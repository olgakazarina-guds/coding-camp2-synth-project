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

## Key OOP Relationships

### Inheritance (is-a / ▷)
* **Oscillator** is an abstract base class defining `virtual float generateSample() = 0`.
* **SineOscillator**, **SquareOscillator**, and **SawOscillator** inherit from `Oscillator` and implement specific DSP mathematical algorithms polymorphically.

### Composition (has-a / ◆)
* **Synth** composes multiple `Voice` instances and `Oscillator` instances.
* Each **Voice** composes an `Envelope` instance to shape the note's ADSR amplitude over time.

### Association (uses / ⇢)
* **Visualizer** reads output audio buffer data from `Synth` via `getBuffer()` to render real-time waveforms without blocking the audio thread.

---

## Team Interface Contract

| Component | Responsibility | Agreed Interface / Method | Contract Notes |
| :--- | :--- | :--- | :--- |
| **Oscillator Base** | Mohammed | `float generateSample()` | Returns float sample in `[-1.0, 1.0]` (0 arguments) |
| **Pitch Control** | Mohammed | `void setFrequency(float hz)` | Updates oscillator pitch |
| **Waveform Selector** | Shared | `setWaveType(WaveType)` / `getWaveType()` | Strongly-typed `WaveType` enum (`SINE`, `SQUARE`, `SAW`) |
| **Voice Binding** | Olga | `Voice::setOscillator(Oscillator*)` | Voice holds base-class pointer polymorphically |
| **Audio Buffer Hook** | Olga | `const std::vector<float>& getBuffer()` | Returns internal mono buffer for Visualizer |
| **Visualizer Hook** | Mohammed | `Visualizer::setSynth(Synth*)` | Visualizer reads audio stream from Synth pointer |
| **Sample Rate** | Shared | `44100 Hz` | Unified global sample rate |

---

## Project Structure

```text
├── src/
│   ├── main.cpp                  # Application entry point
│   ├── ofApp.h / ofApp.cpp       # Main openFrameworks application & event loop
│   ├── Synth.h / Synth.cpp       # Audio engine container & audioOut() stream
│   ├── Voice.h / Voice.cpp       # Polyphonic note manager & oscillator binding
│   ├── Envelope.h                # ADSR volume envelope generator
│   ├── WaveType.h                # Shared WaveType enum (SINE, SQUARE, SAW)
│   ├── Oscillator.h              # Abstract Oscillator base & Sine/Square/Saw classes
│   └── Visualizer.h / Visualizer.cpp # Real-time waveform & spectrum visualizer
└── README.md
