using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StartButton : MonoBehaviour
{
    public GameObject startButton;
    public GameHandler gameHandler;

    public void onClick()
    {
        hideButton();
        gameHandler.startGame();
    }

    public void hideButton() // hide button
    {
        startButton.SetActive(false);
    }
    
    public void showButton() // show buttons
    {
        startButton.SetActive(true);
    }
}
