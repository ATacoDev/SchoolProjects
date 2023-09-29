using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameHandler : MonoBehaviour
{
    public StartButton startMenuButton;
    public StartButton startGameButton;

    public GameObject startScreen;
    public GameObject gameScreen;

    public Paddle paddleP1;
    public Paddle paddleP2;
    
    public Ball ball;

    void Start()
    {
        startMenuButton.showButton();
        startGameButton.hideButton();
        startScreen.SetActive(true);
        gameScreen.SetActive(false);
        ball.freezeBall();
    }

    public void startGame() // go from start screen to game screen
    {
        startScreen.SetActive(false);
        gameScreen.SetActive(true);
        startGameButton.showButton();
    }

    public void unfreezePaddles()
    {
        paddleP1.unfreezePaddles(); 
        paddleP2.unfreezePaddles();
    }

    public void unfreezeBall()
    {
        ball.unfreezeBall();
        ball.AddBallStartingForce();
    }
}
