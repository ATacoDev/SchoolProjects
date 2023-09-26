using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameHandler : MonoBehaviour
{
    public StartButton startMenuButton;
    public StartButton startGameButton;

    public GameObject startScreen;
    public GameObject gameScreen;
    
    void Start()
    {
        startMenuButton.showButton();
        startGameButton.hideButton();
        startScreen.SetActive(true);
        gameScreen.SetActive(false);
    }

    public void startGame() // go from start screen to game screen
    {
        startScreen.SetActive(false);
        gameScreen.SetActive(true);
        startGameButton.showButton();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
