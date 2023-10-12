# FinancerApp

Welcome to the Finance Tracker App, a simple tool to help you achieve your financial goals by tracking your contributions towards a target amount. This app allows you to set a financial goal, add money periodically, and view your financial progress. Your contributions are stored in a "logs.txt" file, and the app displays the last 10 transaction logs.

## Features

- Set a financial target.
- Add money to your goal.
- View the last 10 transaction logs.
- Track your progress toward your financial goal.

## Getting Started

These instructions will help you set up and use the Finance Tracker App on your local machine. The app is built using CMake and Qt, so you will need to install the necessary dependencies.

### Prerequisites

To build and run this app, you need:

- CMake: [Download and Install CMake](https://cmake.org/download/).
- Qt Framework: You'll need the Qt libraries. To install Qt, follow the official installation instructions for your platform: [Qt Installation Guide](https://www.qt.io/download).

### Installation

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/your-username/finance-tracker-app.git

   Navigate to the project directory:

bash

cd finance-tracker-app

Create a build directory and navigate to it:

bash

mkdir build
cd build

Run CMake to configure the build:

bash

cmake ..

Build the app:

bash

make

Run the app:

bash

    ./FinanceTrackerApp

The app will start, and you can interact with it through the graphical user interface.
Usage

    Setting a Financial Goal:
        When you run the app, you will be prompted to set a financial goal by entering the target amount.

    Adding Money:
        You can add money to your financial goal by entering the amount you wish to add. The app will keep a record of your transactions in the "logs.txt" file.

    Viewing Logs:
        You can view the last 10 transaction logs to track your progress. These logs are stored in the "logs.txt" file and are displayed in the app.

Sample Log Entry

Each log entry in the "logs.txt" file will look like this:

less

Transaction Date: [Date and Time]
Amount Added: [Amount Added]
Remaining Balance: [Remaining Balance]

Contributing

Contributions to this project are welcome! If you'd like to contribute, please open an issue or submit a pull request. For major changes, discuss the proposed changes in an issue first.
License

This project is licensed under the MIT License.
Acknowledgments

Special thanks to the creators and contributors of the CMake and Qt libraries.
