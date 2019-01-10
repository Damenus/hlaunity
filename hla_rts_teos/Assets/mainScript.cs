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
        return "playerData: ID" + ID + " pozX: " + posX + " pozY: " + posY + " pozZ: " + posZ;
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
        return "vehicleData: ID" + ID + " pozX: " + posX + " pozY: " + posY + " pozZ: " + posZ;
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

    // Use this for initialization
    void Start () {
        Connect();
        PublishPlayer();
        PublishVehicle();
        SubscribeVehicle();

        int id;

        playerData = new PlayerData();
        id = CreatePlayer();
        Debug.Log("player id: "+id);
        playerData.ID = id;

        id = CreateVehicle();
        Debug.Log("vehicle id: " + id);
    }
	
	// Update is called once per frame
	void Update ()
	{
	    playerData.posX = 0;
	    playerData.posY = 0;
	    playerData.posZ = 0;

	    playerData.rotX = 0;
	    playerData.rotY = 0;
	    playerData.rotZ = 0;

	    playerData.velX = 0;
	    playerData.velY = 0;
	    playerData.velZ = 0;

        UpdatePlayer(playerData);


        //get vehicles
	    int size = 0;
	    IntPtr dataPtr = GetVehicles(ref size);
	    if (size > 0)
	    {
	        VehicleData[] dataFromHla = new VehicleData[size];

	        int offset = 0;
	        int dataVehicleSize = Marshal.SizeOf(typeof(VehicleData));
	        for (int i = 0; i < size; i++, offset += dataVehicleSize)
	        {
	            dataFromHla[i] = (VehicleData)Marshal.PtrToStructure(new IntPtr(dataPtr.ToInt32() + offset), typeof(VehicleData));
	            Debug.Log(dataFromHla[i]);
            }
        }	    
	}
    void OnDestroy()
    {
        Debug.Log("Destroy");
        Disconnect();
    }
}
