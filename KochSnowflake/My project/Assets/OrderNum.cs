using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.SceneManagement;

public class OrderNum : MonoBehaviour
{
    [SerializeField]
    private TMPro.TextMeshProUGUI ordernum;
    private int trueOrder = 1;
    // Start is called before the first frame update
    void Start()
    {
        ordernum = GetComponent<TMPro.TextMeshProUGUI>();
        ordernum.text = "Order: 1";
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyUp(KeyCode.I) || Input.GetKeyUp(KeyCode.O)){
            trueOrder++;
            ordernum.text = "Order: " + trueOrder;
        }
        if (trueOrder >=10)
        {
            Debug.Log("Snowflake is too complex to render anymore points, restarting scene...");
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
        }
    }
}
