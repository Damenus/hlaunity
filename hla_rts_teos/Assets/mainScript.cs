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


public class mainScript : MonoBehaviour {
    [DllImport("hlaPlugin_x64")]
    public static extern void Connect();
    [DllImport("hlaPlugin_x64")]
    public static extern void Disconnect();
    [DllImport("hlaPlugin_x64")]
    public static extern void PublishPlayer();
    [DllImport("hlaPlugin_x64")]
    public static extern void PublishVehicle();
    [DllImport("hlaPlugin_x64")]
    public static extern void SubscribeVehicle();

    [DllImport("hlaPlugin_x64")]
    public static extern int CreatePlayer();
    [DllImport("hlaPlugin_x64")]
    public static extern int CreateVehicle();

    [DllImport("hlaPlugin_x64")]
    public static extern void UpdatePlayer(PlayerData playerData);
    [DllImport("hlaPlugin_x64")]
    public static extern IntPtr GetVehicles(ref int size);

    PlayerData playerData;
    Rigidbody playerRigbody;
    public GameObject player;
    public GameObject tank;
    // Use this for initialization
    void Start ()
    {
        playerRigbody = player.GetComponent<Rigidbody>();
        Connect();
        PublishPlayer();
        SubscribeVehicle();

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

        Debug.Log(playerData);
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
	            Debug.Log(dataFromHla[i]);
            }

	        tank.transform.position=new Vector3(dataFromHla[0].posX,dataFromHla[0].posY,dataFromHla[0].posZ);
	        tank.transform.rotation = Quaternion.Euler(dataFromHla[0].rotX, dataFromHla[0].rotY, dataFromHla[0].rotZ);
        }	    
	}
    void OnDestroy()
    {
        Debug.Log("Destroy");
        Disconnect();
    }
}
