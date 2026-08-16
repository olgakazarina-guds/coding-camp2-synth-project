# OpenFrameworks Software Synthesizer & Visualizer

A real-time C++ polyphonic software synthesizer and reactive visualizer built with **openFrameworks v0.11.2** for **Coding Camp II (Project 2)**.

---

## 👥 Authors & Task Division

- **Olga (Left UML Architecture)** — Audio Engine, Voice & Envelope
  - `Synth`: Core audio engine container and `audioOut(ofSoundBuffer &buffer)` stream callback.
  - `Voice`: Polyphonic note management and oscillator binding.
  - `Envelope`: ADSR envelope generator shaping volume over time.
  - Variable & Interface Contracts.

- **Mohammed (Right UML Architecture)** — Oscillator DSP & Visualizer
  - `Oscillator`: Abstract base class with pure virtual `generateSample()` interface.
  - Waveform Subclasses: `SineOscillator`, `SquareOscillator`, and `SawOscillator` (Inheritance).
  - `Visualizer`: Real-time oscilloscope waveform & FFT frequency spectrum rendering.

- **Joint / Shared Collaboration**
  - Continuous integration and interface synchronization (`generateSample()`, `sampleRate`, `frequency`, `triggerNote()`, `setADSR()`, `WaveType`).
  - Comprehensive Lab Report, user manual, and performance testing.
  - Continuous progress logging on Yellowdig.

---

## 🏗️ Object-Oriented Architecture (OOP)

The application models sound synthesis strictly following our design UML class diagram:

```text
┌──────────────────────────────────────┐                   ┌──────────────────────────────────────┐
│                Synth                 │─── reads buffer ─>│              Visualizer              │
│       Audio engine, audioOut()       │                   │       Draws waveform / spectrum      │
└──────────────────────────────────────┘                   └──────────────────────────────────────┘
        │                              │
     composes                       composes
        │                              │
        ▼                              ▼
┌──────────────────────────────────────┐                   ┌──────────────────────────────────────┐
│                Voice                 │                   │        Oscillator «abstract»         │
│           One playing note           │                   │           generateSample()           │
└──────────────────────────────────────┘                   └──────────────────────────────────────┘
        │                                                                     ▲
     composes                                                                 │
        │                                                     ┌───────────────┼───────────────┐
        ▼                                                     │               │               │
┌──────────────────────────────────────┐             ┌─────────────────┐ ┌───────────────┐ ┌───────────────┐
│               Envelope               │             │ SineOscillator  │ │SquareOscillator│ │ SawOscillator │
│       Shapes volume over time        │             └─────────────────┘ └───────────────┘ └───────────────┘
└──────────────────────────────────────┘
