using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public TMP_Text scoreText;
    public int score;

    public void Update()
    {
        scoreText.text = getScore();
    }

    public string getScore()
    {
        return score.ToString();
    }

    public void increaseScore()
    {
        score++;
    }

}
