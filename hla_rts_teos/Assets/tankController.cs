using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class tankController : MonoBehaviour
{

    public int ID;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void setTank(Vector3 position, Quaternion rotation, Vector3 velocity)
    {
        transform.position = position;
        transform.rotation = rotation;
    }
}
