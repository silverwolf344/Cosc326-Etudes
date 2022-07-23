using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

[RequireComponent(typeof(LineRenderer))]

public class KochLine : KochGenerator
{
    LineRenderer lRenderer;
    [Range(0f,1f)]
    public float lerpAmount;
    float totaltime = 1f;
    float currtime = 0f;
    Vector3[] lerpPos;
    public float genMultiply = 1f;
    // Start is called before the first frame update
    void Start()
    {
        lRenderer = GetComponent<LineRenderer>();
        lRenderer.positionCount = position.Length;
        lRenderer.SetPositions(position);

    }

    // Update is called once per frame
    void Update()
    {
        if (genCount != 0){
            for (int i=0; i < position.Length; i++) {
                // Raise the new points of the snowflake over time if the button is pressed/new sides are added
                currtime += Time.deltaTime;
                lerpPos[i] = Vector3.Lerp(position[i], targetPosition[i], currtime / totaltime);
            }
            
            lRenderer.SetPositions(lerpPos);
        }

        if(Input.GetKeyUp(KeyCode.O)){ 
            // If O is pressed, generate new Outwards points

            KochGenny(targetPosition, true, genMultiply);
            lerpPos = new Vector3[position.Length];
            lRenderer.positionCount = position.Length;
            lRenderer.SetPositions(position);
            lerpAmount = 0;
            currtime = 0f;
        } else if(Input.GetKeyUp(KeyCode.I)) {
            // If I is pressed, generate new Inwards Points
            KochGenny(targetPosition, false, genMultiply);
            lerpPos = new Vector3[position.Length];
            lRenderer.positionCount = position.Length;
            lRenderer.SetPositions(position);
            lerpAmount = 0;
            currtime = 0f;
        } else if (Input.GetKeyUp(KeyCode.R)) {
            // Reload Scene, Resetting Shape
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
        }
    }
}
