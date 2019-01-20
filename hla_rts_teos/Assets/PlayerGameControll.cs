using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;
using UnityStandardAssets.Effects;

public class PlayerGameControll : MonoBehaviour
{
    public GameObject weapon;

    private GameObject barrelEnd;

    private shootManager shootManager;
	// Use this for initialization
	void Start ()
	{
	    barrelEnd = weapon.transform.GetChild(0).gameObject;
	    shootManager = GameObject.Find("gameManager").GetComponent<shootManager>();
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void shootFromPlayer()
    {
        shootManager.ShootPlayer(barrelEnd);
    }
}
