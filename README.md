Overview
This project is a Kahoot-like trivia game that allows players to join quizzes, answer multiple-choice questions, and compete for the highest score. It is designed for both individual and group play, with real-time tracking of player progress and scores.

The project was developed in collaboration with a friend of mine, where I developed the backend in C++ and SQL, while the frontend was created by my partner using C#.

Features
  1. Player authentication and session management
  2. Real-time trivia quizzes with multiple-choice questions
  3. Score tracking and leaderboards
  4. Support for multiple players in each session
  5. Dynamic question loading from a database
  6. Cross-platform compatibility (frontend in C#, backend in C++)
     
Project Structure
  1. Backend (C++ & SQL)
  2. Handles player authentication and session management
  3. Connects to a SQL database that stores quiz questions, player information, and scores
  4. Manages game logic, including handling answers and calculating scores
  5. Communicates with the frontend using a network protocol to transmit game data
