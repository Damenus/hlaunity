using System.Collections;
using System.Collections.Generic;
using UnityEngine.AI;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class TankControler : MonoBehaviour
{

    Camera cam;

    public GameObject tank1;
    public GameObject tank2;
    public GameObject tank3;
    public GameObject tank4;


    public LayerMask groundLayer;
    NavMeshAgent tankAgent1;
    NavMeshAgent tankAgent2;
    NavMeshAgent tankAgent3;
    NavMeshAgent tankAgent4;

    public Button button1;
    public Button button2;
    public Button button3;
    public Button button4;

    public Toggle toggle1;
    public Toggle toggle2;
    public Toggle toggle3;
    public Toggle toggle4;

    bool buttonBool1;
    bool buttonBool2;
    bool buttonBool3;
    bool buttonBool4;


    void Start()
    {

        tankAgent1 = tank1.GetComponent<NavMeshAgent>();
        tankAgent2 = tank2.GetComponent<NavMeshAgent>();
        tankAgent3 = tank3.GetComponent<NavMeshAgent>();
        tankAgent4 = tank4.GetComponent<NavMeshAgent>();

        button1.onClick.AddListener(MyFunction1);
        button2.onClick.AddListener(MyFunction2);
        button3.onClick.AddListener(MyFunction3);
        button4.onClick.AddListener(MyFunction4);

        MyFunction1();

    }

    void MyFunction1()
    {
        button1.image.color = new Color(68, 69, 85,0);
        button2.image.color = new Color(185, 182, 186, 1);
        button3.image.color = new Color(185, 182, 186,1);
        button4.image.color = new Color(185, 182, 186,1);

        buttonBool1 = true;
        buttonBool2 = false;
        buttonBool3 = false;
        buttonBool4 = false;

        cam.transform.position = new Vector3(tank1.transform.position.x, 100, tank1.transform.position.z);  // new Vector3(0, 20, 0);
    }
    void MyFunction2()
    {
        button1.image.color = new Color(185, 182, 186, 1);
        button2.image.color = new Color(68, 69, 85, 0);
        button3.image.color = new Color(185, 182, 186, 1);
        button4.image.color = new Color(185, 182, 186, 1);

        buttonBool1 = false;
        buttonBool2 = true;
        buttonBool3 = false;
        buttonBool4 = false;

        cam.transform.position = new Vector3(tank2.transform.position.x, 100, tank2.transform.position.z); 
    }
    void MyFunction3()
    {
        button1.image.color = new Color(185, 182, 186, 1);
        button2.image.color = new Color(185, 182, 186, 1);
        button3.image.color = new Color(68, 69, 85, 0);
        button4.image.color = new Color(185, 182, 186, 1);

        buttonBool1 = false;
        buttonBool2 = false;
        buttonBool3 = true;
        buttonBool4 = false;

        cam.transform.position = new Vector3(tank3.transform.position.x, 100, tank3.transform.position.z);
    }
    void MyFunction4()
    {
        button1.image.color = new Color(185, 182, 186, 1);
        button2.image.color = new Color(185, 182, 186, 1);
        button3.image.color = new Color(185, 182, 186, 1);
        button4.image.color = new Color(68, 69, 85, 0);
        buttonBool1 = false;
        buttonBool2 = false;
        buttonBool3 = false;
        buttonBool4 = true;

        cam.transform.position = new Vector3(tank4.transform.position.x, 100, tank4.transform.position.z);

    }

    void Awake()
    {
        cam = Camera.main;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButton(1))
        {
            if (buttonBool1)
                if (tank1 != null)
                    tankAgent1.SetDestination(GetPointUnderCursor());
            if (buttonBool2)
                if (tank2 != null)
                    tankAgent2.SetDestination(GetPointUnderCursor());
            if (buttonBool3)
                if (tank3 != null)
                    tankAgent3.SetDestination(GetPointUnderCursor());
            if (buttonBool4) 
                if (tank4 != null)
                    tankAgent4.SetDestination(GetPointUnderCursor());
        }

    }

    private Vector3 GetPointUnderCursor()
    {
        /*
        Vector2 screenPosition = Input.mousePosition;
        Vector3 mouseWorldPosition = cam.ScreenToWorldPoint(screenPosition);
 
        RaycastHit hitPosition;

        Physics.Raycast(mouseWorldPosition, cam.transform.forward, out hitPosition, Mathf.Infinity, groundLayer);

        return hitPosition.point;
         */
        Vector3 mouse = Input.mousePosition;
        Ray castPoint = Camera.main.ScreenPointToRay(mouse);
        RaycastHit hit;
        Physics.Raycast(castPoint, out hit, Mathf.Infinity, groundLayer);
        return hit.point;

    }
}
