using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KochGenerator : MonoBehaviour
{
    protected enum _initiator {
        // Types of shapes (Other ones for fun)
        Triangle,
        Square,
        Pentagon,
        Hexagon
    }

    public struct LineSegment {
        // Contains variables to declare for linesegments 
        public Vector3 StartPosition { get; set; }
        public Vector3 EndPosition { get; set; }
        public Vector3 Direction { get; set; }
        public float Length { get; set; }
    }
    // Initialize the enum
    [SerializeField]
    protected _initiator initiator = new _initiator();
    [SerializeField]
    protected AnimationCurve generator;
    protected Keyframe[] keys;

    protected int genCount;

    protected int pointAmount;
    private Vector3[] snowflakePoints;
    private Vector3 rotateVector;
    private float initialRotation;

    [SerializeField]
    protected float initSize;

    private Vector3 rotateAxis;

    protected Vector3[] position;
    protected Vector3[] targetPosition;
    // Array of Sides of the shape, eg 3 sides of a triangle...
    private List<LineSegment> lineSegments;

    private void OnDrawGizmos(){
        SetSnowflakePoints();
        snowflakePoints = new Vector3[pointAmount];

        rotateVector = new Vector3(0,0,1);
        rotateAxis = new Vector3(0,1,1);


        for (int i = 0; i < pointAmount; i++){
            // Scale the point to selected size
            snowflakePoints[i] = rotateVector * initSize;
            // Correct rotation based on amount of points and selected axis
            rotateVector = Quaternion.AngleAxis(360 / pointAmount, rotateAxis) * rotateVector;
        }
        for (int i = 0; i < pointAmount; i++){
            // For every point of the snowflake
            Gizmos.color = Color.white;
            // Allows unity editor to move around draw Gizmos around the scene 
            Matrix4x4 rotationMatrix = Matrix4x4.TRS(transform.position, transform.rotation, transform.lossyScale);
            Gizmos.matrix = rotationMatrix;
            // If not on last line, draw to next point in the point list
            if(i < pointAmount - 1){
                Gizmos.DrawLine(snowflakePoints[i], snowflakePoints[i + 1]);
            } else {
                // Otherwise it is the last line, so connect to the first one
                Gizmos.DrawLine(snowflakePoints[i], snowflakePoints[0]);
            }
        }

    }

    private void SetSnowflakePoints(){
        // Set correct pointcount of shape (this is for fun and future use as I'm going to use fractals in a personal project)
        switch(initiator){
            case _initiator.Triangle:
                pointAmount = 3;
                break;
            case _initiator.Square:
                pointAmount = 4;
                break;
            case _initiator.Pentagon:
                pointAmount = 5;
                break;
            case _initiator.Hexagon:
                pointAmount = 6;
                break;
            default:
                pointAmount = 3;
                break;
        };
    }
    private void Awake() {
        SetSnowflakePoints();
        

        // Assign lists and arrays
        position = new Vector3[pointAmount+1];
        targetPosition = new Vector3[pointAmount+1];
        keys = generator.keys;
        lineSegments = new List<LineSegment>();
        rotateVector = new Vector3(0,0,1);
        rotateAxis = new Vector3(0,-1,1);


        for (int i = 0; i < pointAmount; i++){
            // Scale the point to selected size
            position[i] = rotateVector * initSize;
            // Correct rotation based on amount of points and selected axis
            rotateVector = Quaternion.AngleAxis(360 / pointAmount, rotateAxis) * rotateVector;
        }
        position[pointAmount] = position[0];
        targetPosition = position;
        
    }

    protected void KochGenny(Vector3[] positions, bool outwards, float generatorMultiplier){
        /// <summary> Generates the added Koch shape to the sides of the shape. </summary>
        /// <param name="positions">An array of x,y,z coordinates of the shape.</param>
        /// <param name="generatorMultiplier">A multiplier to change the height of the added shapes if needed </param>
        /// <param name="outwards">A bool to toggle if the new shapes go inwards or outwards out of the shape</param>


        
        // Temporary local lists for specific side of the shape
        List<Vector3> newPos = new List<Vector3>();
        List<Vector3> targetPos = new List<Vector3>();
        Vector3 movePos;
        Vector3 Dir;
        float moveAmount;
        float heightAmount;
        // Clear the list as the shape will change, this line cost me 2 hours of debugging as the line renderer-
        // was drawing over itself multiple times 
        lineSegments.Clear();
        // This forloop creates a list of the sides of the current order of the snowflake
        for (int i = 0; i < positions.Length -1; i++){
            LineSegment side = new LineSegment();
            side.StartPosition = positions[i];
            if (i == positions.Length - 1){
                // If last side of shape, set end position to start position
                side.EndPosition = positions[0];
            } else {
                side.EndPosition = positions[i+1];
            }
            side.Direction = (side.EndPosition - side.StartPosition).normalized;
            side.Length = Vector3.Distance(side.EndPosition, side.StartPosition);
            // Add to the array
            lineSegments.Add(side);
        }

        // Iterate through line segments and calculate new points of the shape/line to generate snowflake shape
        for (int i = 0; i < lineSegments.Count; i++) {
            // Eg One Third of Side Position
            newPos.Add(lineSegments[i].StartPosition);
            targetPos.Add(lineSegments[i].StartPosition);

            // Iterate through key points and calculate the amount they move and the amount they are raised
            for (int j = 1; j < keys.Length - 1; j++){
                // Key Points is a unity wave draw thingy so:
                // There are three points
                // The First point is Time: 0.333 (one third), Value: 0
                // The Second is Time: 0.5 (one half), Value: 0.25
                // The Third is Time: 0.666 (two thirds), Value: 0
                // So it looks like this : __/\__
                // It is used to generate the extra triangles on each side of the snowflake.
                moveAmount = lineSegments[i].Length * keys[j].time; // How far along the side
                heightAmount = (lineSegments[i].Length * keys[j].value) * generatorMultiplier; // How high to raise the second point
                movePos = lineSegments[i].StartPosition + (lineSegments[i].Direction * moveAmount); 
                // Change wether or not to generate new shape inwards or outwards
                if (outwards){
                    Dir = Quaternion.AngleAxis(-90, rotateAxis) * lineSegments[i].Direction;
                } else {
                    Dir = Quaternion.AngleAxis(90, rotateAxis) * lineSegments[i].Direction;
                }
                // Middle Part of side, part that rises! Top of triangle.
                newPos.Add(movePos);
                targetPos.Add(movePos + (Dir * heightAmount));
            }
            // Two Thirds of side position
            newPos.Add(lineSegments[i].EndPosition);
            targetPos.Add(lineSegments[i].EndPosition);
        }
        // Add temporary/local lists to the global lists
        newPos.Add(lineSegments[0].StartPosition);
        targetPos.Add(lineSegments[0].StartPosition);
        position = new Vector3[newPos.Count];
        targetPosition = new Vector3[targetPos.Count];
        position = newPos.ToArray();
        targetPosition = targetPos.ToArray();

        genCount++;

    }

}
