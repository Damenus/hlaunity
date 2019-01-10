using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public struct Square
{
    public float posX;
    public float posY;
}



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

    // Use this for initialization
    void Start () {
        Connect();
        PublishPlayer();
        SubscribeVehicle();

        int id;
        id = CreatePlayer();
        Debug.Log("id: "+id);
        id = CreatePlayer();
        Debug.Log("id: " + id);
        id = CreatePlayer();
        Debug.Log("id: " + id);
        id = CreatePlayer();
        Debug.Log("id: " + id);
    }
	
	// Update is called once per frame
	void Update () {
	}
    void OnDestroy()
    {
        Debug.Log("Destroy");
        Disconnect();
    }
}
