# ETL Engine

ETL Engine is a C++20 project designed for extracting, transforming, and loading financial data from APIs. It fetches ETF data, validates it using a JSON schema, and organizes it into directories based on stock exchanges.

## Features

- **API Fetching**: Retrieves data from financial APIs.
- **JSON Validation**: Ensures data conforms to a predefined schema.
- **Data Organization**: Categorizes data into directories by stock exchange.

## Requirements

- **C++20** compatible compiler.
- **CMake** 3.26 or above.
- Libraries: `cURL`, `nlohmann_json`, `valijson` (install via [Vcpkg](https://vcpkg.io)).

## Setup

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd etl_engine
   ```
2. Install dependencies:
   ```bash
   vcpkg install curl nlohmann-json valijson
   ```
3. Add your API key to `src/.env`:
   ```plaintext
   API_KEY=<your_api_key>
   ```
4. Build the project:
   ```bash
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg_toolchain>
   cmake --build build
   ```
5. Run the application:
   ```bash
   ./etl_engine
   ```

## Directory Structure

- `data/`: Output files organized by exchange.
- `schemas/`: JSON schema (e.g., `schema.json`).
- `src/`: Source code and `.env` file for API key.

## Usage

- Fetches ETF data from `https://financialmodelingprep.com/api/v3/etf/list`.
- Validates data using `schemas/schema.json`.
- Output saved in `data/<Exchange Name>/`.

## License

This project is licensed under the MIT License.