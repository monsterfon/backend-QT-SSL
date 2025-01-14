# Back-End QT-SSL Project

This repository contains a **client-server** project developed using **C++**, **Qt**, and **SSL** (Secure Sockets Layer) to demonstrate secure communication with certificates and cryptographic principles. The project showcases the use of **object-oriented programming** and emphasizes **SSL** security features, including the use of **certificates** and **certificate authorities (CAs)**. 

## Projects Overview

### SSL Encryption and Authentication
The main objective of this project is to implement a secure communication channel between a **client** and a **server** using **SSL/TLS** protocols. The server and client exchange data only if they possess the **correct credentials**, ensuring secure communication.

- **Client-Server Architecture**: The project consists of two distinct parts—one for the **server** and one for the **client**. Both communicate with each other only if the certificates match.
- **SSL/TLS Encryption**: The project highlights how SSL is essential for securing data in transit. It ensures confidentiality, data integrity, and authentication between the client and server.
- **Certificates and Certificate Authorities (CAs)**: The project involves creating and managing certificates, as well as understanding how **CAs** issue and validate these certificates to ensure trust between the communicating parties.
- **API**: An **API** was created for easy integration with other systems. The API is still being used today and provides a way to interact with the server securely.

### Technologies and Tools Used:
- **C++** for implementing the back-end logic and secure communication.
- **Qt (Professional Version)** for building the graphical user interface and handling the SSL functionality.
- **OpenSSL** for implementing SSL protocols and working with certificates.
- **Visual Studio** as the integrated development environment (IDE) for building the project.

## Features
- Secure communication between the client and server using **SSL** encryption.
- Both **client** and **server** require **matching certificates** to authenticate each other, ensuring only authorized parties can communicate.
- Use of **certificate authorities** to manage and validate certificates.
- A fully functional **API** that is still used today for secure communication.
- Object-oriented programming principles used throughout the project to ensure clean and maintainable code.

## How to Run

1. Clone the repository.
2. Open the project in **Visual Studio**.
3. Ensure you have the professional version of **Qt** installed.
4. Build and run the server and client.
   - The server waits for connections from clients.
   - The client needs to provide the correct certificate to establish a secure connection.
5. The client and server communicate securely, verifying credentials through the certificates.

---

This project provides an in-depth demonstration of **SSL/TLS encryption**, **certificate management**, and **client-server communication**. It also reinforces the importance of secure communication in modern applications and helped deepen my understanding of **cryptography** and **object-oriented programming** in C++.
