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
};


public class mainScript : MonoBehaviour {
    [DllImport("hlaPlugin_x64")]
    public static extern void Connect();
    [DllImport("hlaPlugin_x64")]
    public static extern void Disconnect();
    [DllImport("hlaPlugin_x64")]
    public static extern void PublishPlayer();

    [DllImport("hlaPlugin_x64")]
    public static extern void SubscribeVehicle();

    [DllImport("hlaPlugin_x64")]
    public static extern int CreatePlayer();

    [DllImport("hlaPlugin_x64")]
    public static extern void UpdatePlayer(PlayerData playerData);

    PlayerData playerData;

    // Use this for initialization
    void Start () {
        Connect();
        PublishPlayer();
        SubscribeVehicle();

        int id;

        playerData = new PlayerData();
        id = CreatePlayer();
        Debug.Log("id: "+id);
        playerData.ID = id;
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
	}
    void OnDestroy()
    {
        Debug.Log("Destroy");
        Disconnect();
    }
}
