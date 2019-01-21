using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;

public struct ShotData
{
    public float shotPosX;
    public float shotPosY;
    public float shotPosZ;
    public float hitPosX;
    public float hitPosY;
    public float hitPosZ;

    public override String ToString()
    {
        return "shotData shot pozX: " + shotPosX + " pozY: " + shotPosY + " pozZ: " + shotPosZ + " hit pozX: " + hitPosX + " pozY: " + hitPosY + " pozZ: " + hitPosZ;
    }
};

public struct PlayerData
{
    public int ID;
    public float posX;
    public float posY;
    public float posZ;
    public float rotX;
    public float rotY;
    public float rotZ;
    public float velX;
    public float velY;
    public float velZ;

    public override String ToString()
    {
        return "playerData: ID" + ID + " pozX: " + posX + " pozY: " + posY + " pozZ: " + posZ;
    }
};

public struct VehicleData
{
    public int ID;
    public float posX;
    public float posY;
    public float posZ;
    public float rotX;
    public float rotY;
    public float rotZ;
    public float velX;
    public float velY;
    public float velZ;

    public override String ToString()
    {
        return "vehicleData: ID" + ID + " pozX: " + posX + " pozY: " + posY + " pozZ: " + posZ + " rotX: "+rotX+" rotY: "+rotY+" rotZ: "+rotZ;
    }
};


public class hlaScript : MonoBehaviour
{
    [DllImport("hlaPlugin_x64")]
    public static extern void Connect();
    [DllImport("hlaPlugin_x64")]
    public static extern void Disconnect();
    [DllImport("hlaPlugin_x64")]
    public static extern void PublishPlayer();
    [DllImport("hlaPlugin_x64")]
    public static extern void PublishVehicle();
    [DllImport("hlaPlugin_x64")]
    public static extern void SubscribeVehicle();
    [DllImport("hlaPlugin_x64")]
    public static extern void SubscribePlayer();

    [DllImport("hlaPlugin_x64")]
    public static extern int CreatePlayer();
    [DllImport("hlaPlugin_x64")]
    public static extern int CreateVehicle();
    [DllImport("hlaPlugin_x64")]
    private static extern void PublishShot();
    [DllImport("hlaPlugin_x64")]
    private static extern void SubscribeShot();

    [DllImport("hlaPlugin_x64")]
    public static extern void UpdatePlayer(PlayerData playerData);
    [DllImport("hlaPlugin_x64")]
    public static extern void UpdateVehicle(VehicleData tank1Data);
    [DllImport("hlaPlugin_x64")]
    public static extern IntPtr GetVehicles(ref int size);
    [DllImport("hlaPlugin_x64")]
    public static extern IntPtr GetPlayers(ref int size);

    [DllImport("hlaPlugin_x64")]
    private static extern void SendShot(ShotData shotData);
    [DllImport("hlaPlugin_x64")]
    private static extern IntPtr GetShots(ref int size);

    private shootManager shootManager;

    PlayerData playerData;
    VehicleData tank1Data;
    VehicleData tank2Data;
    VehicleData tank3Data;
    VehicleData tank4Data;

    public GameObject player;
    public GameObject tank1;
    public GameObject tank2;
    public GameObject tank3;
    public GameObject tank4;

    // Use this for initialization
    void Start()
    {
        shootManager = GetComponent<shootManager>();
        Connect();
        PublishVehicle();
        SubscribePlayer();
        PublishShot();
        SubscribeShot();

        int id, idVehicle1, idVehicle2, idVehicle3, idVehicle4;

   //     playerData = new PlayerData();
    //    id = CreatePlayer();
   //     Debug.Log("player id: " + id);
   //     playerData.ID = id;

        idVehicle1 = CreateVehicle();
        idVehicle2 = CreateVehicle();
        idVehicle3 = CreateVehicle();
        idVehicle4 = CreateVehicle();

        Debug.Log("vehicle id: " + idVehicle1);
        Debug.Log("vehicle id: " + idVehicle2);
        Debug.Log("vehicle id: " + idVehicle3);
        Debug.Log("vehicle id: " + idVehicle4);

        tank1Data.ID = idVehicle1;
        tank2Data.ID = idVehicle2;
        tank3Data.ID = idVehicle3;
        tank4Data.ID = idVehicle4;
    }

    // Update is called once per frame
    void Update()
    {
        if (tank1 != null)
        {
            tank1Data.posX = tank1.transform.position.x;
            tank1Data.posY = tank1.transform.position.y;
            tank1Data.posZ = tank1.transform.position.z;

            tank1Data.rotX = tank1.transform.eulerAngles.x;
            tank1Data.rotY = tank1.transform.eulerAngles.y;
            tank1Data.rotZ = tank1.transform.eulerAngles.z;

            tank1Data.velX = 0;
            tank1Data.velY = 0;
            tank1Data.velZ = 0;
            //  Debug.Log(tank1Data);
            UpdateVehicle(tank1Data);
        }

        if (tank2 != null)
        {
            tank2Data.posX = tank2.transform.position.x;
            tank2Data.posY = tank2.transform.position.y;
            tank2Data.posZ = tank2.transform.position.z;

            tank2Data.rotX = tank2.transform.eulerAngles.x;
            tank2Data.rotY = tank2.transform.eulerAngles.y;
            tank2Data.rotZ = tank2.transform.eulerAngles.z;

            tank2Data.velX = 0;
            tank2Data.velY = 0;
            tank2Data.velZ = 0;
            //   Debug.Log(tank2Data);
            UpdateVehicle(tank2Data);
        }

        if (tank3 != null)
        {
            tank3Data.posX = tank3.transform.position.x;
            tank3Data.posY = tank3.transform.position.y;
            tank3Data.posZ = tank3.transform.position.z;

            tank3Data.rotX = tank3.transform.eulerAngles.x;
            tank3Data.rotY = tank3.transform.eulerAngles.y;
            tank3Data.rotZ = tank3.transform.eulerAngles.z;

            tank3Data.velX = 0;
            tank3Data.velY = 0;
            tank3Data.velZ = 0;
            // Debug.Log(tank3Data);
            UpdateVehicle(tank3Data);
        }


        if (tank4 != null)
        {
            tank4Data.posX = tank4.transform.position.x;
            tank4Data.posY = tank4.transform.position.y;
            tank4Data.posZ = tank4.transform.position.z;

            tank4Data.rotX = tank4.transform.eulerAngles.x;
            tank4Data.rotY = tank4.transform.eulerAngles.y;
            tank4Data.rotZ = tank4.transform.eulerAngles.z;

            tank4Data.velX = 0;
            tank4Data.velY = 0;
            tank4Data.velZ = 0;
            // Debug.Log(tank4Data);
            UpdateVehicle(tank4Data);
        }


        //get player
        
        int size = 0;
        IntPtr dataPtr = GetPlayers(ref size);
        if (size > 0)
        {
            PlayerData[] dataFromHla = new PlayerData[size];

            int offset = 0;
            int dataVehicleSize = Marshal.SizeOf(typeof(PlayerData));
            for (int i = 0; i < size; i++, offset += dataVehicleSize)
            {
                dataFromHla[i] = (PlayerData)Marshal.PtrToStructure(new IntPtr(dataPtr.ToInt32() + offset), typeof(PlayerData));
                //Debug.Log(dataFromHla[i]);

                player.transform.position = new Vector3(dataFromHla[i].posX, dataFromHla[i].posY, dataFromHla[i].posZ);
                player.transform.rotation = Quaternion.Euler(0,dataFromHla[i].rotY,0);
            }
        }

        //get shots
        size = 0;
        dataPtr = GetShots(ref size);
        if (size > 0)
        {
            Debug.Log("rozmiar strzałow: " + size);
            ShotData[] dataFromHla = new ShotData[size];

            int offset = 0;
            int dataShotSize = Marshal.SizeOf(typeof(ShotData));
            for (int i = 0; i < size; i++, offset += dataShotSize)
            {
                dataFromHla[i] = (ShotData)Marshal.PtrToStructure(new IntPtr(dataPtr.ToInt32() + offset), typeof(ShotData));
                Debug.Log(dataFromHla[i]);
                Vector3 shotPosition = new Vector3(dataFromHla[i].shotPosX, dataFromHla[i].shotPosY, dataFromHla[i].shotPosZ);
                Vector3 hitPosition = new Vector3(dataFromHla[i].hitPosX, dataFromHla[i].hitPosY, dataFromHla[i].hitPosZ);
                shootManager.playExplosion(new Vector3(dataFromHla[i].shotPosX, dataFromHla[i].shotPosY, dataFromHla[i].shotPosZ), new Vector3(dataFromHla[i].hitPosX, dataFromHla[i].hitPosY, dataFromHla[i].hitPosZ));

                float distance;
                if (tank1 != null)
                {
                    distance = Vector3.Distance(hitPosition, tank1.transform.position);
                    //Debug.Log("Dystans: " + distance + "pozycja strzału: " + hitPosition + " pozycja gracza: " + playerRigbody.transform.position + "odleglosc obliczona: ");
                    if (distance < (float)15)
                    {
                        tank1.GetComponent<TankMenager>().TakeDamage(100, hitPosition);
                        Debug.Log("--die-- dystans: " + distance);
                    }
                }

                if (tank2 != null)
                {
                    distance = Vector3.Distance(hitPosition, tank2.transform.position);
                    if (distance < (float)15)
                    {
                        tank2.GetComponent<TankMenager>().TakeDamage(100, hitPosition);
                        Debug.Log("--die-- dystans: " + distance);
                    }
                }

                if (tank3 != null)
                {
                    distance = Vector3.Distance(hitPosition, tank3.transform.position);
                    if (distance < (float)15)
                    {
                        tank3.GetComponent<TankMenager>().TakeDamage(100, hitPosition);
                        Debug.Log("--die-- dystans: " + distance);
                    }
                }

                if (tank4 != null)
                {
                    distance = Vector3.Distance(hitPosition, tank4.transform.position);
                    if (distance < (float)15)
                    {
                        tank4.GetComponent<TankMenager>().TakeDamage(100, hitPosition);
                        Debug.Log("--die-- dystans: " + distance);
                    }
                }
            
            }

        }

        
    }
    void OnDestroy()
    {
        Debug.Log("Destroy");
        Disconnect();
    }

    public void registerShoot(Vector3 shotPos, Vector3 hitPos)
    {
        ShotData toSend = new ShotData();
        toSend.shotPosX = shotPos.x;
        toSend.shotPosY = shotPos.y;
        toSend.shotPosZ = shotPos.z;
        toSend.hitPosX = hitPos.x;
        toSend.hitPosY = hitPos.y;
        toSend.hitPosZ = hitPos.z;
        SendShot(toSend);
    }
    /*
    private void addTank(VehicleData[] tankDatas)
    {
        foreach (VehicleData vehicleData in tankDatas)
        {
            if (!tanks.Exists(x => x.ID == vehicleData.ID))
            {
                //tanks doesn't exist
                GameObject tmpTank = Instantiate(tankModel, new Vector3(vehicleData.posX, vehicleData.posY, vehicleData.posZ), Quaternion.Euler(vehicleData.rotX, vehicleData.rotY, vehicleData.rotZ));
                tmpTank.GetComponent<tankController>().ID = vehicleData.ID;
                tanks.Add(tmpTank.GetComponent<tankController>());
            }
        }
    }
    private void removeTank(VehicleData[] tankDatas)
    {
        foreach (tankController tank in tanks)
        {
            bool noExist = true;
            foreach (VehicleData tankData in tankDatas)
            {
                if (tank.ID == tankData.ID)
                {
                    noExist = false;
                }
            }
            if (noExist)
            {
                tanks.Remove(tank);
                tank.destroy();
            }
        }
    }
    private void updateTank(VehicleData[] tankDatas)
    {
        foreach (VehicleData tankData in tankDatas)
        {
            tankController tmp = tanks.Find(x => x.ID == tankData.ID);
            tmp.setTank(new Vector3(tankData.posX, tankData.posY, tankData.posZ), Quaternion.Euler(tankData.rotX, tankData.rotY, tankData.rotZ), new Vector3(tankData.velX, tankData.velY, tankData.velZ));
        }
    }
    */
}
