using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PaddleP1 : MonoBehaviour
{

   public GameObject paddle;

   public void Update()
   {
      Move();
      // if paddle hits a border, print ("Paddle hit a border") to console
   }

   private void Move() // move the paddle
   {
      if (Input.GetKey(KeyCode.S))
      {
         transform.Translate(Vector3.down * Time.deltaTime * 10f);
      }
      else if (Input.GetKey(KeyCode.W))
      {
         transform.Translate(Vector3.up * Time.deltaTime * 10f);
      }
   }

   private void CollisionHandler(Collision2D collision)
   {
      if (collision.gameObject.CompareTag("Border"))
      {
         Debug.Log("Paddle hit a border");
      }
   }
   
}
