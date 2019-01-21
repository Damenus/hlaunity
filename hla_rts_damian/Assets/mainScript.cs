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
    public static extern Square GetSquare();

    public GameObject mainSquare;
    public Square square2d;

    // Use this for initialization
    void Start () {
        mainSquare = GameObject.Find("mainSquare");
        //Connect();
	}
	
	// Update is called once per frame
	void Update () {
       // square2d = GetSquare();
       // mainSquare.transform.position = new Vector3(square2d.posX, (float)0.5, square2d.posY);
	}
}
