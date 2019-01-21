using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;
using System.Diagnostics;
using UnityEngine.Internal.Experimental.UIElements;
using Debug = UnityEngine.Debug;

[StructLayout(LayoutKind.Sequential)]
public struct PlayerData {
    public int ID;
    public float posX;
    public float posY;
    public float posZ;
    public float rotX;
    public float rotY;
    public float rotZ;
    public float velX;
    public float velY;
    public float velZ;

    public override String ToString()
    {
        return "playerData: ID" + ID + " pozX: " + posX + " pozY: " + posY + " pozZ: " + posZ + " rotX: " + rotX + " rotY: " + rotY + " rotZ: " + rotZ + " velZ: " + velZ + " velY: " + velY + " velZ: " + velZ;
    }
};
[StructLayout(LayoutKind.Sequential)]
public struct VehicleData
{
    public int ID;
    public float posX;
    public float posY;
    public float posZ;
    public float rotX;
    public float rotY;
    public float rotZ;
    public float velX;
    public float velY;
    public float velZ;

    public override String ToString()
    {
        return "vehicleData: ID" + ID + " pozX: " + posX + " pozY: " + posY + " pozZ: " + posZ + " rotX: " + rotX + " rotY: " + rotY + " rotZ: " + rotZ + " velZ: " + velZ + " velY: " + velY + " velZ: " + velZ;
    }
};
[StructLayout(LayoutKind.Sequential)]
public struct ShotData
{
    public float shotPosX;
    public float shotPosY;
    public float shotPosZ;
    public float hitPosX;
    public float hitPosY;
    public float hitPosZ;

    public override String ToString()
    {
        return "shotData shot pozX: " + shotPosX + " pozY: " + shotPosY + " pozZ: " + shotPosZ+" hit pozX: " + hitPosX + " pozY: " + hitPosY + " pozZ: " + hitPosZ;
    }
};


public class mainScript : MonoBehaviour {
    [DllImport("hlaPlugin_x64")]
    private static extern void Connect();
    [DllImport("hlaPlugin_x64")]
    private static extern void Disconnect();
    [DllImport("hlaPlugin_x64")]
    private static extern void PublishPlayer();
    [DllImport("hlaPlugin_x64")]
    private static extern void PublishVehicle();
    [DllImport("hlaPlugin_x64")]
    private static extern void SubscribeVehicle();
    [DllImport("hlaPlugin_x64")]
    private static extern void PublishShot();
    [DllImport("hlaPlugin_x64")]
    private static extern void SubscribeShot();

    [DllImport("hlaPlugin_x64")]
    private static extern void SendShot(ShotData shotData);
    [DllImport("hlaPlugin_x64")]
    private static extern IntPtr GetShots(ref int size);

    [DllImport("hlaPlugin_x64")]
    private static extern int CreatePlayer();
    [DllImport("hlaPlugin_x64")]
    private static extern int CreateVehicle();

    [DllImport("hlaPlugin_x64")]
    private static extern void UpdatePlayer(PlayerData playerData);
    [DllImport("hlaPlugin_x64")]
    private static extern IntPtr GetVehicles(ref int size);

    PlayerData playerData;
    Rigidbody playerRigbody;
    private shootManager shootManager;
    public GameObject player;
    public GameObject tankModel;

    private GameObject gameOverPanel; 
    private List<tankController> tanks;
    // Use this for initialization
    void Start ()
    {
        gameOverPanel = GameObject.Find("GameOver");
        gameOverPanel.SetActive(false);
        shootManager = GetComponent<shootManager>();
        playerRigbody = player.GetComponent<Rigidbody>();
        Connect();
        PublishPlayer();
        SubscribeVehicle();
        PublishShot();
        SubscribeShot();
        tanks = new List<tankController>();
        int id;

        playerData = new PlayerData();
        id= CreatePlayer();
        Debug.Log("player id: "+id);
        playerData.ID = id;

    }
	
	// Update is called once per frame
	void Update ()
	{
	    playerData.posX = player.transform.position.x;
	    playerData.posY = player.transform.position.y;
	    playerData.posZ = player.transform.position.z;

	    playerData.rotX = player.transform.eulerAngles.x;
	    playerData.rotY = player.transform.eulerAngles.y;
	    playerData.rotZ = player.transform.eulerAngles.z;

	    playerData.velX = playerRigbody.velocity.x;
	    playerData.velY = playerRigbody.velocity.y;
	    playerData.velZ = playerRigbody.velocity.z;

        //Debug.Log(playerData);
        UpdatePlayer(playerData);

        //get vehicles
	    int size = 0;
	    IntPtr dataPtr = GetVehicles(ref size);
	    if (size > 0)
	    {
            //Debug.Log("rozmiar: "+size);
	        VehicleData[] dataFromHla = new VehicleData[size];
	        try
	        {
                int offset = 0;
	            int dataVehicleSize = Marshal.SizeOf(typeof(VehicleData));
	            for (int i = 0; i < size; i++, offset += dataVehicleSize)
	            {
	                dataFromHla[i] = (VehicleData) Marshal.PtrToStructure(new IntPtr(dataPtr.ToInt32() + offset),typeof(VehicleData));

                }

	            if (size > tanks.Count)
	            {
                    addTank(dataFromHla);
	            }
                else if (size < tanks.Count)
	            {
	                removeTank(dataFromHla);
                }
                updateTank(dataFromHla);
	        }
	        catch (NullReferenceException e)
	        {
	            Debug.Log("wyjatek: " + e.Message);
	            //throw e;
	        }

        }
	    Marshal.FreeCoTaskMem(dataPtr);
        //get shots
        size = 0;
	    IntPtr dataPtrShot = GetShots(ref size);
	    if (size > 0)
	    {
	        Debug.Log("rozmiar strzałow: " + size);
	        ShotData[] dataFromHla = new ShotData[size];

	        int offset = 0;
	        int dataShotSize = Marshal.SizeOf(typeof(ShotData));
	        for (int i = 0; i < size; i++, offset += dataShotSize)
	        {
	            dataFromHla[i] = (ShotData)Marshal.PtrToStructure(new IntPtr(dataPtrShot.ToInt32() + offset), typeof(ShotData));
	            //Debug.Log("strzął: "+dataFromHla[i]);
	            Vector3 shotPosition = new Vector3(dataFromHla[i].shotPosX, dataFromHla[i].shotPosY,dataFromHla[i].shotPosZ);
	            Vector3 hitPosition = new Vector3(dataFromHla[i].hitPosX, dataFromHla[i].hitPosY, dataFromHla[i].hitPosZ);
                shootManager.playExplosion(shotPosition,hitPosition);

	            float distance = Vector3.Distance(hitPosition, player.transform.position);
                Debug.Log("Dystans: "+distance+ "pozycja strzału: " + hitPosition + " pozycja gracza: "+playerRigbody.transform.position+ "odleglosc obliczona: ");
                if (distance < (float) 5)
	            {
                    Debug.Log("--die-- dystans: " + distance);
	                gameOverPanel.SetActive(true);
                }
            }
            
	    }
	    Marshal.FreeCoTaskMem(dataPtrShot);
    }
    void OnDestroy()
    {
        Debug.Log("Destroy");
        Disconnect();
    }

    public void registerShoot(Vector3 shotPos, Vector3 hitPos)
    {
        ShotData toSend = new ShotData();
        toSend.shotPosX = shotPos.x;
        toSend.shotPosY = shotPos.y;
        toSend.shotPosZ = shotPos.z;
        toSend.hitPosX = hitPos.x;
        toSend.hitPosY = hitPos.y;
        toSend.hitPosZ = hitPos.z;
        //Debug.Log(toSend);
        SendShot(toSend);
    }

    private void addTank(VehicleData[] tankDatas)
    {
        foreach (VehicleData vehicleData in tankDatas)
        {
            if (!tanks.Exists(x => x.ID == vehicleData.ID))
            {
                //tanks doesn't exist
                GameObject tmpTank = Instantiate(tankModel, new Vector3(vehicleData.posX, vehicleData.posY, vehicleData.posZ), Quaternion.Euler(vehicleData.rotX, vehicleData.rotY, vehicleData.rotZ));
                tmpTank.GetComponent<tankController>().ID = vehicleData.ID;
                tanks.Add(tmpTank.GetComponent<tankController>());
            }
        }
    }
    private void removeTank(VehicleData[] tankDatas)
    {
        foreach (tankController tank in tanks)
        {
            bool noExist = true;
            foreach (VehicleData tankData in tankDatas)
            {
                if (tank.ID == tankData.ID)
                {
                    noExist = false;
                }
            }
            if (noExist)
            {
                tanks.Remove(tank);
                tank.destroy();
            }
        }
    }
    private void updateTank(VehicleData[] tankDatas)
    {
        foreach (VehicleData tankData in tankDatas)
        {
            tankController tmp = tanks.Find(x => x.ID == tankData.ID);
            tmp.setTank(new Vector3(tankData.posX, tankData.posY, tankData.posZ), Quaternion.Euler(tankData.rotX, tankData.rotY, tankData.rotZ),new Vector3(tankData.velX, tankData.velY, tankData.velZ));
        }
    }
}
