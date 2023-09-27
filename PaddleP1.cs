using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PaddleP1 : Paddle
{

   public GameObject paddle;
   private Vector2 _direction;

   private void FixedUpdate()
   {
      if (_direction.sqrMagnitude != 0)
      {
         _rigidbody.AddForce(_direction * speed);
      }
   }
   private void Update()
   {
      if (Input.GetKey(KeyCode.S))
      {
         transform.Translate(Vector2.down * Time.deltaTime * 10f);
         _direction = Vector2.down;
      }
      else if (Input.GetKey(KeyCode.W))
      {
         transform.Translate(Vector2.up * Time.deltaTime * 10f);
         _direction = Vector2.up;
      }
      else
      {
         _direction = Vector2.zero;
      }
   }

}
