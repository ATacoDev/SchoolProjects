using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class Ball : MonoBehaviour
{
    private Rigidbody2D _rigidbody;

    public float speed = 400.0f;

    private void Awake()
    {
        _rigidbody = GetComponent<Rigidbody2D>();
    }

    public void freezeBall()
    {
        _rigidbody.constraints = RigidbodyConstraints2D.FreezeAll;
    }
    
    public void unfreezeBall()
    {
        _rigidbody.constraints = RigidbodyConstraints2D.FreezeRotation;
    }

    public void Reset()
    {
        this.transform.position = Vector3.zero;
    }

    public void AddBallStartingForce()
    {
        float x = Random.value < 0.5f ? -1.0f : 1.0f; // if less then half (left), if greater (right)
        float y = Random.value < 0.5f ? Random.Range(-1.0f, -0.5f) : Random.Range(0.5f, 1.0f); // if 0, ball would go perfectly horizontal
        Vector2 direction = new Vector2(x, y);
        _rigidbody.AddForce(direction * this.speed);
    }
}
