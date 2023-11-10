using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ComputerPaddle: Paddle
{
    public Rigidbody2D ball;
    private void FixedUpdate()
    {
        if (this.ball.velocity.x > 0.0f)
        {
            if (this.ball.position.y > this._rigidbody.position.y)
            {
                _rigidbody.AddForce(Vector2.up * speed);
            }
            else if (this.ball.position.y < this._rigidbody.position.y)
            {
                _rigidbody.AddForce(Vector2.down * speed);
            }
        }
        else
        {
            if (this.transform.position.y > 0.0f)
            {
                _rigidbody.AddForce(Vector2.down * this.speed);
            } else if (this.transform.position.y < 0.0f)
            {
                _rigidbody.AddForce(Vector2.up * this.speed);
            }
        }
    }
}
