using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class shootManager : MonoBehaviour
{
    public GameObject explosion;

    public float playerExplosionSize;
    public float playerRange;
    public float tankExplosionSize;
    public float tankRange;
    public float hitExplosionSize;

    private mainScript _mainScript;
    // public float player

    // Use this for initialization
    void Start ()
    {
        _mainScript = GetComponent<mainScript>();
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    public void ShootPlayer(GameObject barrelEnd)
    {
        shoot(barrelEnd,playerExplosionSize,playerRange);
    }
    public void ShootTank(GameObject barrelEnd)
    {
        shoot(barrelEnd, tankExplosionSize, tankRange);
    }

    public void shoot(GameObject barrelEnd,float explosionSize,float range)
    {
        Debug.DrawRay(barrelEnd.transform.position, barrelEnd.transform.forward * range);

        Vector3 shotPos, hitPos;

        shotPos = barrelEnd.transform.position;
        GameObject tmpShootExplosion = Instantiate(explosion,shotPos, Quaternion.identity);
        tmpShootExplosion.transform.localScale = new Vector3(explosionSize, explosionSize, explosionSize);
        tmpShootExplosion.GetComponent<ParticleSystem>().Play();
        Destroy(tmpShootExplosion, tmpShootExplosion.GetComponent<ParticleSystem>().duration);

        RaycastHit hit;
        Ray ray = new Ray();
        if (Physics.Raycast(barrelEnd.transform.position, barrelEnd.transform.forward, out hit, range))
        {
            hitPos = hit.point;
        }
        else
        {
            hitPos = barrelEnd.transform.position + barrelEnd.transform.forward * range;
        }
        GameObject tmpHitExplosion = Instantiate(explosion,hitPos, Quaternion.identity);
        tmpHitExplosion.transform.localScale = new Vector3(hitExplosionSize, hitExplosionSize, hitExplosionSize);
        tmpHitExplosion.GetComponent<ParticleSystem>().startDelay = 0.2f;
        tmpHitExplosion.GetComponent<ParticleSystem>().Play();
        Destroy(tmpHitExplosion, tmpHitExplosion.GetComponent<ParticleSystem>().duration);
        _mainScript.registerShoot(shotPos,hitPos);
    }

    public void playExplosion(Vector3 shotPosition,Vector3 hitPosition)
    {
        GameObject tmpShootExplosion = Instantiate(explosion, shotPosition, Quaternion.identity);
        tmpShootExplosion.transform.localScale = new Vector3(playerExplosionSize, playerExplosionSize, playerExplosionSize);
        tmpShootExplosion.GetComponent<ParticleSystem>().Play();
        Destroy(tmpShootExplosion, tmpShootExplosion.GetComponent<ParticleSystem>().duration);

        GameObject tmpHitExplosion = Instantiate(explosion, hitPosition, Quaternion.identity);
        tmpHitExplosion.transform.localScale = new Vector3(hitExplosionSize, hitExplosionSize, hitExplosionSize);
        tmpHitExplosion.GetComponent<ParticleSystem>().startDelay = 0.2f;
        tmpHitExplosion.GetComponent<ParticleSystem>().Play();
        Destroy(tmpHitExplosion, tmpHitExplosion.GetComponent<ParticleSystem>().duration);
    }
}
