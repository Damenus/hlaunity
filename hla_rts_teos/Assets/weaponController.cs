using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class weaponController : MonoBehaviour
{
    public ParticleSystem Explosion;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void shoot()
    {
        Explosion.Play();
    }
}
