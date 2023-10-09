using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sound : MonoBehaviour
{
    public AudioSource audioSource;
    private AudioClip backgroundMusic;

    private void Awake()
    {
        audioSource.Play();
    }
}
