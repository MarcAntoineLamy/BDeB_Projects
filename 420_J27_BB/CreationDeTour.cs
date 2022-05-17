/*
 * Travail pratique 1 - Creation de tour
 * Created by Marc-Antoine Beaudet-Lamy
 * 9 mai 2022
 */
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;
using Random = UnityEngine.Random;

public class CreationDeTour : MonoBehaviour
{
    public bool isPyramid = false; // Determine if the tower created is normal or a pyramid
    public Vector3 towerPosition = Vector3.zero; // Center of the created tower
    [Min(1)]
    public uint numberOfFloor = 5; // Number of floor to be generated
    [Min(2)]
    public int structureWitdh = 10; // Width of the structure
    [Min(0)]
    public float cubeScalling = 1f; // Base scalling of the object
    [Min(0)]
    public int scalingVariation = 15; // Variation in scaling in pourcent
    [Min(1)]
    public int objectLenghtVariation = 1; // Variation if the object lenght

    // Direction to go in asquare pattern
    private static readonly int[] directionsX = { 1, 0, -1, 0 }; // X direction
    private static readonly int[] directionsZ = { 0, 1, 0, -1 }; // Y direction

    private int buildingCount = 0; // Used to keep count of building

    private void OnEnable()
    {
        GameObject buildingParent = new GameObject("Structure_" + buildingCount);
        buildingParent.transform.position = towerPosition;
        createObject("Center", buildingParent, Vector3.zero, Vector3.one * cubeScalling);

        if (!isPyramid)
            createTower(buildingParent);
        else
            createPyramide(buildingParent);

        buildingCount++;
    }
    GameObject createObject(string name, GameObject parent, Vector3 pos, Vector3 scale)
    {
        pos.y += scale.y * .5f; // Putting the object on the floor

        GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
        cube.transform.SetParent(parent.transform, false);
        cube.name = name;
        cube.transform.localScale = scale;
        cube.transform.localPosition = pos;

        return cube;
    }
    void createTower(GameObject parent)
    {
        // Taking 1 from the lenght because the last object of the line is the start of the other one
        int lineLenght = structureWitdh - 1;

        // starting to build from the -x and -z corner and keep track of where we are at
        float currentX = -(lineLenght / 2f);
        float currentZ = -(lineLenght / 2f);

        // Building from the ground up
        for (int g = 0; g < numberOfFloor; g++)
        {
            int objectCounter = 0;

            GameObject floorParent = new GameObject("Floor_" + g);
            floorParent.transform.SetParent(parent.transform, false);

            // Going in each direction
            for (int i = 0; i < directionsX.Length; i++)
            {
                // Building one line in that direction
                for (int j = 0; j < lineLenght; j++)
                {
                    // Updating where we are at
                    currentX += directionsX[i];
                    currentZ += directionsZ[i];

                    // Condition to NOT create an object
                    if (g == numberOfFloor - 1 && (i * lineLenght + j) % 2 == 1 && numberOfFloor != 1)
                        continue; // Skip this loop

                    float cubeLenght = Random.Range(1, objectLenghtVariation + 1); // Randomize the lenght of the object
                    cubeLenght = cubeLenght > lineLenght - j - 1 ? lineLenght - j - 1 : cubeLenght; // Make sure that the lenght of the object is not bigger than the remaining lenght

                    // Base position and scalling
                    Vector3 pos = new Vector3(currentX, g, currentZ) * cubeScalling;
                    Vector3 scale = Vector3.one * cubeScalling;

                    if ((g < numberOfFloor - 1 || numberOfFloor == 1) && j != lineLenght - 1)
                    {
                        // Altereation of position and scalling if not the last floor or is the only floor and not a corner
                        if (directionsX[i] == 0)
                        {
                            // If moving in the Z axis
                            scale.z *= cubeLenght; // change the lenght to the random lenght
                            pos.z += (((cubeLenght - 1) / 2) * cubeScalling) * directionsZ[i]; // Adapt the positioin to reflect the new lenght
                            currentZ += (cubeLenght - 1) * directionsZ[i]; // Update our current position to start the next object at the right place

                            scale.x *= (float)Random.Range(100 - scalingVariation, 100) / 100; // Apply the scaling variation on the side opposed to the direction
                        }
                        else
                        {
                            // If moving in the X axis
                            scale.x *= cubeLenght;
                            pos.x += (((cubeLenght - 1) / 2) * cubeScalling) * directionsX[i];
                            currentX += (cubeLenght - 1) * directionsX[i];

                            scale.z *= (float)Random.Range(100 - scalingVariation, 100) / 100;
                        }

                        j += (int)cubeLenght - 1; // SKip the number of block to compensate for the lenght
                    }
                    else if (j != lineLenght - 1 && g == numberOfFloor - 1)
                    {
                        // If the last floor or not a corner, apply the maximum variation so the obect is always smaller than the cube below
                        scale.x *= 1f - ((float)scalingVariation / 100);
                        scale.z *= 1f - ((float)scalingVariation / 100);
                    }

                    // Create the object
                    createObject("Brick_" + ++objectCounter, floorParent, pos, scale);
                }
            }
        }
    }
    void createPyramide(GameObject parent)
    {
        // Taking 1 from the lenght because the last object of the line is the start of the other one
        int lineLenght = structureWitdh - 1;

        // starting to build from the -x and -z corner and keep track of where we are at
        float currentX = -(lineLenght / 2f);
        float currentZ = -(lineLenght / 2f);

        // Calcul the height of the pyramid
        int height = (int)Mathf.Ceil((float)structureWitdh / 2);

        // Building from the ground up
        for (int g = 0; g < height; g++)
        {
            int objectCounter = 0;

            GameObject floorParent = new GameObject("Floor_" + g);
            floorParent.transform.SetParent(parent.transform, false);

            // Going in each direction
            for (int i = 0; i < directionsX.Length; i++)
            {
                // Building one line in that direction
                for (int j = 0; j < lineLenght; j++)
                {
                    // Updating where we are at
                    currentX += directionsX[i];
                    currentZ += directionsZ[i];

                    // Base position and scalling
                    Vector3 pos = new Vector3(currentX, g, currentZ) * cubeScalling;
                    Vector3 scale = Vector3.one * cubeScalling;

                    // Variate the scaling 
                    scale *= 1 + ((float)Random.Range(0, scalingVariation) / 100);

                    createObject("Brick_" + objectCounter++, floorParent, pos, scale);
                }
            }

            // If the top and a odd witdh
            if (g == height - 1 && structureWitdh % 2 == 1)
            {
                createObject("Brick_0", floorParent, new Vector3(currentX, g, currentZ) * cubeScalling, Vector3.one * cubeScalling);
            }

            // reduce the lenght of the line by 2 (1 on each side)
            lineLenght -= 2;

            // Move the starting corner toward the inside
            currentX++;
            currentZ++;
        }

    }
}
