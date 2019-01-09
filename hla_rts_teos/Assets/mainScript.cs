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
    public static extern void PublishPlayer();

    // Use this for initialization
    void Start () {
        Connect();
        PublishPlayer();
	}
	
	// Update is called once per frame
	void Update () {
	}
}
