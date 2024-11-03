#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits>
#include <type_traits>
#include <functional>

using namespace std;

// Lambda functionality
template <typename Func, typename... Args>
inline auto callLambda(Func &&func, Args &&...args) -> decltype(func(args...))
{
    return func(forward<Args>(args)...);
}

// General-purpose function to take user input of various types
template <typename T>
T input(const string &prompt = "")
{
    while (true)
    {
        cout << prompt;
        string userInput;
        getline(cin, userInput);

        try
        {
            if constexpr (is_same<T, int>::value)
            {
                return stoi(userInput);
            }
            else if constexpr (is_same<T, long>::value)
            {
                return stol(userInput);
            }
            else if constexpr (is_same<T, char>::value)
            {
                if (userInput.length() == 1 && !isdigit(userInput[0]))
                {
                    return userInput[0];
                }
                else
                {
                    throw invalid_argument("Invalid input. Please enter a single character.");
                }
            }
            else if constexpr (is_same<T, string>::value)
            {
                return userInput;
            }
            else if constexpr (is_same<T, bool>::value)
            {
                if (userInput == "true" || userInput == "1")
                {
                    return true;
                }
                else if (userInput == "false" || userInput == "0")
                {
                    return false;
                }
                else
                {
                    throw invalid_argument("Invalid input. Please enter 'true' or 'false'.");
                }
            }
            else if constexpr (is_same<T, float>::value)
            {
                return stof(userInput);
            }
            else if constexpr (is_same<T, double>::value)
            {
                return stod(userInput);
            }
            else
            {
                static_assert(!is_same<T, T>::value, "Unsupported type.");
            }
        }
        catch (const invalid_argument &)
        {
            cout << "Invalid input. Please try again." << endl;
        }
        catch (const out_of_range &)
        {
            cout << "Input is out of range. Please try again." << endl;
        }
    }
}

// Function to print formatted output
template <typename... Args>
inline void print(const std::string &fmt, Args &&...args)
{
    std::ostringstream formatted;
    std::string::size_type start = 0, end;
    int arg_index = 0;

    // Replace {} with the provided arguments
    ((formatted << fmt.substr(start, (end = fmt.find("{}", start)) - start) << args,
      start = end + 2, arg_index++),
     ...);

    formatted << fmt.substr(start);
    std::cout << formatted.str() << std::endl;
}

// Overloaded print function for direct string input
inline void print(const std::string &message)
{
    std::cout << message << std::endl;
}

// Overloaded print function for direct variable input
template <typename T>
inline void print(const T &value)
{
    std::cout << value << std::endl;
}

// String indexing feature (similar to Python slicing) with negative support
string slice(const string &str, int start, int stop, int step = 1)
{
    string result;
    if (step == 0)
        throw invalid_argument("Step cannot be zero.");

    // Adjust negative indices
    if (start < 0)
        start += str.size();
    if (stop < 0)
        stop += str.size();

    // Handle out-of-bounds for start and stop
    if (start < 0)
        start = 0;
    if (stop > str.size())
        stop = str.size();

    // Include the start index character and include the stop index character
    for (int i = start; (step > 0 ? i <= stop : i >= stop); i += step)
    {
        if (i < 0 || i >= str.size())
            break; // Out of bounds check
        result += str[i];
    }
    return result;
}