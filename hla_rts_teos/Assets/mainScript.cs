using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

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
    public GameObject tank; 

    private int tankNumber;
    // Use this for initialization
    void Start ()
    {
        shootManager = GetComponent<shootManager>();
        playerRigbody = player.GetComponent<Rigidbody>();
        Connect();
        PublishPlayer();
        SubscribeVehicle();
        PublishShot();
        SubscribeShot();
        tankNumber = 0;
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
            Debug.Log("rozmiar: "+size);
	        VehicleData[] dataFromHla = new VehicleData[size];

	        int offset = 0;
	        int dataVehicleSize = Marshal.SizeOf(typeof(VehicleData));
	        for (int i = 0; i < size; i++, offset += dataVehicleSize)
	        {
	            dataFromHla[i] = (VehicleData)Marshal.PtrToStructure(new IntPtr(dataPtr.ToInt32() + offset), typeof(VehicleData));
            }

	        if (size > tankNumber)
	        {

	        }
            else if (size < tankNumber)
	        {

	        }

	        tank.transform.position=new Vector3(dataFromHla[0].posX,dataFromHla[0].posY,dataFromHla[0].posZ);
	        tank.transform.rotation = Quaternion.Euler(dataFromHla[0].rotX, dataFromHla[0].rotY, dataFromHla[0].rotZ);
        }
	    //get shots
	    size = 0;
	    dataPtr = GetShots(ref size);
	    if (size > 0)
	    {
	        Debug.Log("rozmiar strzałow: " + size);
	        ShotData[] dataFromHla = new ShotData[size];

	        int offset = 0;
	        int dataShotSize = Marshal.SizeOf(typeof(ShotData));
	        for (int i = 0; i < size; i++, offset += dataShotSize)
	        {
	            dataFromHla[i] = (ShotData)Marshal.PtrToStructure(new IntPtr(dataPtr.ToInt32() + offset), typeof(ShotData));
	            Debug.Log(dataFromHla[i]);
	            shootManager.playExplosion(new Vector3(dataFromHla[i].shotPosX, dataFromHla[i].shotPosY, dataFromHla[i].shotPosZ), new Vector3(dataFromHla[i].hitPosX, dataFromHla[i].hitPosY, dataFromHla[i].hitPosZ));
            }
            
	    }
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
        SendShot(toSend);
    }

    private void addTank()
    {

    }
}
