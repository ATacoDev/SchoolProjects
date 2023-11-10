using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public TMP_Text scoreText;
    public int score;
    public GameHandler gameHandler;

    public void Update()
    {
        scoreText.text = getScore();
        gameHandler.checkIfGameOver();
    }

    public string getScore()
    {
        return score.ToString();
    }
    
    public int getScoreInt()
    {
        return score;
    }

    public void increaseScore()
    {
        score++;
    }

    public void reset()
    {
        score = 0;
    }

}
