using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameHandler : MonoBehaviour
{
    public StartButton startMenuButton;
    public StartButton startGameButton;

    public GameObject startScreen;
    public GameObject gameScreen;
    public GameObject winScreen;
    public GameObject loseScreen;

    public Paddle paddleP1;
    public Paddle paddleP2;

    public Ball ball;

    public Score playerScore;
    public Score computerScore;

    private bool gameDone;
    private int winner = -1;

    void Start()
    {
        startMenuButton.showButton();
        startGameButton.hideButton();
        startScreen.SetActive(true);
        gameScreen.SetActive(false);
        ball.freezeBall();
        winScreen.SetActive(false);
        loseScreen.SetActive(false);
        gameDone = false;
        winner = -1; // 0 for player, 1 for computer
    }

    private void Update()
    {
        checkIfGameOver();
    }

    public void startGame() // go from start screen to game screen
    {
        startScreen.SetActive(false);
        gameScreen.SetActive(true);
        startGameButton.showButton();
    }

    public void reset()
    {
        playerScore.reset();
        computerScore.reset();
        ball.freezeBall();
        ball.Reset();
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

    public void playerScoresBall()
    {
        playerScore.increaseScore();
        ball.Reset();
        resetPaddles();
    }

    public void computerScoresBall()
    {
        computerScore.increaseScore();
        ball.Reset();
        resetPaddles();
    }

    public void resetPaddles()
    {
        paddleP1.reset();
        paddleP2.reset();
    }

    public void checkIfGameOver()
    {
        if (computerScore.getScoreInt() == 3)
        {
            gameDone = true;
            winner = 1;
            EndGame();
        } else if (playerScore.getScoreInt() == 3)
        {
            gameDone = true;
            winner = 0;
            EndGame();
        }
        else
        {
            gameDone = false;
        }
    }

    public void EndGame()
    {
        if (gameDone && winner == 0)
        {
            gameScreen.SetActive(false);
            winScreen.SetActive(true);
        } else if (gameDone && winner == 1)
        {
            gameScreen.SetActive(false);
            loseScreen.SetActive(true);
        }
    }

    public void PlayAgain()
    {
        // reset everything and let the user play again
        // reset the paddles and the ball
    }
    
    
}
