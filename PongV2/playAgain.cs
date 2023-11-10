using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playAgain : MonoBehaviour
{
    public GameObject playAgainButton;
    public GameHandler gameHandler;
    public GameObject screen;

    public void onClick()
    {
        hideButton();
        screen.SetActive(false);
        gameHandler.reset();
        gameHandler.startGame();
    }

    public void hideButton() 
    {
        playAgainButton.SetActive(false);
    }
    
    public void showButton() 
    {
        playAgainButton.SetActive(true);
    }
}
