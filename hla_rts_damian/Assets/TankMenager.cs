using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using UnityEngine.AI;

public class TankMenager : MonoBehaviour
{

    public int startingHealth = 100;
    public int currentHealth;
    public float sinkSpeed = 2.5f;
    public int scoreValue = 10;
    public AudioClip deathClip;
    int seeDistance = 50;
    int atakDistance = 50;

    Animator anim;
    AudioSource enemyAudio;
    ParticleSystem hitParticles;
    CapsuleCollider capsuleCollider;
    NavMeshAgent navMeshAgent;
    bool isDead;
    bool isSinking;

    //GameMenager gameMenager;

     private Vector3 _dir;

    public Slider slider;
    GameObject player;

    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
    }

    // Start is called before the first frame update
    void Awake()
    {
        anim = GetComponent<Animator>();
        enemyAudio = GetComponent<AudioSource>();
        hitParticles = GetComponentInChildren<ParticleSystem>();
        capsuleCollider = GetComponent<CapsuleCollider>();
        navMeshAgent = GetComponent<NavMeshAgent>();

        currentHealth = startingHealth;
        slider.value = currentHealth;
        isSinking = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (isSinking)
        {
            transform.Translate(-Vector3.up * sinkSpeed * Time.deltaTime);
        }

       

       // if (Vector2.Distance(transform.position, player.transform.position) < seeDistance)
       // {
            //player.SetActive();
        //}

        if (Vector3.Distance(transform.position, player.transform.position) < atakDistance && navMeshAgent.velocity.x == 0 && navMeshAgent.velocity.z == 0)
        {
            //transform.LookAt(2 * transform.position - player.transform.position);
            var targetRotation = Quaternion.LookRotation(player.transform.position - transform.position);

            // Smoothly rotate towards the target point.
            transform.rotation = Quaternion.Slerp(transform.rotation, targetRotation, 1 * Time.deltaTime);
        }

        if (currentHealth <= 0)
        {
            Death();
        }

    }


    public void TakeDamage(int amount, Vector3 hitPoint)
    {
        if (isDead)
            return;

       // enemyAudio.Play();

        currentHealth -= amount;

       // hitParticles.transform.position = hitPoint;
       // hitParticles.Play();

        if (currentHealth <= 0)
        {
            Death();
        }
    }


    void Death()
    {
        isDead = true;

        //capsuleCollider.isTrigger = true;

        anim.SetTrigger("Dead");

    //    enemyAudio.clip = deathClip;
     //   enemyAudio.Play();
        StartSinking();
    }


    public void StartSinking()
    {
        GetComponent<UnityEngine.AI.NavMeshAgent>().enabled = false;
  //      GetComponent<Rigidbody>().isKinematic = true;
        isSinking = true;
       // ScoreManager.score += scoreValue;
        Destroy(gameObject, 2f);
    }
}
