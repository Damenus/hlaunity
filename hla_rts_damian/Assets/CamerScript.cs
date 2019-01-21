using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CamerScript : MonoBehaviour
{

    float speed = 10.0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
   /*
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            if (Input.GetAxis("Mouse X") > 0)
            {
                transform.position += new Vector3(Input.GetAxisRaw("Mouse X") * Time.deltaTime * speed,
                                           0.0f, Input.GetAxisRaw("Mouse Y") * Time.deltaTime * speed);
            }

            else if (Input.GetAxis("Mouse X") < 0)
            {
                transform.position += new Vector3(Input.GetAxisRaw("Mouse X") * Time.deltaTime * speed,
                                           0.0f, Input.GetAxisRaw("Mouse Y") * Time.deltaTime * speed);
            }
        }
    }
  */

    public float dragSpeed = 10;
    private Vector3 dragOrigin;

    public bool cameraDragging = true;

    public float outerLeft = -100f;
    public float outerRight = 100f;
    public float outerUp = 100f;
    public float outerDown = -100f;


    void Update()
    {



        Vector2 mousePosition = new Vector2(Input.mousePosition.x, Input.mousePosition.y);

        float left = Screen.width * 0.2f;
        float right = Screen.width - (Screen.width * 0.2f);

        if (mousePosition.x < left)
        {
            cameraDragging = true;
        }
        else if (mousePosition.x > right)
        {
            cameraDragging = true;
        }


        if (cameraDragging)
        {

            if (Input.GetMouseButtonDown(0))
            {
                dragOrigin = Input.mousePosition;
                return;
            }

            if (!Input.GetMouseButton(0)) return;

            Vector3 pos = Camera.main.ScreenToViewportPoint(Input.mousePosition - dragOrigin);
            Vector3 move = new Vector3(pos.x * dragSpeed, 0, pos.y * dragSpeed);

            if (move.x > 0f)
            {
                if (this.transform.position.x < outerRight)
                {
                    transform.Translate(move, Space.World);
                }
            }
            else
            {
                if (this.transform.position.x > outerLeft)
                {
                    transform.Translate(move, Space.World);
                }
            }
            if (move.y > 0f)
            {
                if (this.transform.position.z < outerUp)
                {
                    transform.Translate(move, Space.World);
                }
            }
            else
            {
                if (this.transform.position.z > outerDown)
                {
                    transform.Translate(move, Space.World);
                }
            }
        }
    }

    /*
  bool bDragging;
    private Vector3  oldPos;
    private Vector3 panOrigin;
    int panSpeed = 70;

   void Update()
   {
       if (Input.GetMouseButtonDown(0))
       {
           bDragging = true;
           oldPos = transform.position;
           panOrigin = Camera.main.ScreenToViewportPoint(Input.mousePosition);                    //Get the ScreenVector the mouse clicked
       }

       if (Input.GetMouseButton(0))
       {
           Vector3 pos = Camera.main.ScreenToViewportPoint(Input.mousePosition) - panOrigin;    //Get the difference between where the mouse clicked and where it moved
           transform.position = oldPos + -pos * panSpeed;                                         //Move the position of the camera to simulate a drag, speed * 10 for screen to worldspace conversion
       }

       if (Input.GetMouseButtonUp(0))
       {
           bDragging = false;
       }
   }

   

   float X, Y;
   void Update()
   {
       if (Input.GetMouseButton(0))
       {
           transform.Rotate(new Vector3(Input.GetAxis("Mouse Y") * speed, -Input.GetAxis("Mouse X") * speed, 0));
           X = transform.rotation.eulerAngles.x;
           Y = transform.rotation.eulerAngles.y;
           transform.rotation = Quaternion.Euler(X, Y, 0);
       }
   }
    *  */
}
