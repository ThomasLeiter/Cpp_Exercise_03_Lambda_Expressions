#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // Various higher order function examples given
#include <functional> // For std::function wrapper

#include "vector_wrapper.hpp"


/*
 * Prints a std::vector in Python style
 * [1, 2, 3, ...]
 */
template<typename T>
std::ostream& operator<<(std::ostream& str, const std::vector<T>& vec){
    str << "[";
    auto it = vec.cbegin();
    while (it != vec.cend()){
        str << *it;
        if (++it != vec.cend()){
            str << ", ";
        }
    }
    return str << "]";
}

/*
 * Apply function f to all
 * elements of vector vec
 */
std::vector<double> map_int_to_double(const std::vector<int> &vec, double (*f)(int))
{
    std::vector<double> mapped_values;
    for (int u : vec)
    {
        mapped_values.push_back(f(u));
    }
    return mapped_values;
}

/*
 * Apply function f to all
 * elements of vector vec
 */
template <typename U, typename V>
std::vector<V> map_with_function(const std::vector<U> &vec, const std::function<V(U)> &f)
{
    std::vector<V> mapped_values;
    for (U u : vec)
    {
        mapped_values.push_back(f(u));
    }
    return mapped_values;
}

class Person
{
public:
    std::string name;
    int age;
    Person(const std::string &name, const int &age) : name{name}, age{age} {}
};

std::ostream &operator<<(std::ostream &str, const Person &p)
{
    return str << "Person(" << p.name << ", " << p.age << ")";
}

int main()
{
    std::vector<int> vec{1, 1, 2, 3, 5, 8, 13};
    std::cout << vec << '\n';
    // [1, 1, 2, 3, 5, 8, 13]

    // Use all_of to check if all elements fulfill predicate
    bool all_gt_three = std::all_of(vec.cbegin(), vec.cend(), [](int x)
                                    { return x > 3; });
    std::cout << "All greater than three = " << std::boolalpha << all_gt_three << '\n';
    // All greater than three = false

    // Use any_of to check if any element fulfills predicate
    bool any_gt_five = std::any_of(vec.cbegin(), vec.cend(), [](int x)
                                   { return x > 5; });
    std::cout << "Any greater than five = " << std::boolalpha << any_gt_five << '\n';
    // Any greater than five = true

    // Use none_of to check if no element fulfills predicate
    bool none_lt_zero = std::none_of(vec.cbegin(), vec.cend(), [](int x)
                                     { return x < 0; });
    std::cout << "None less than zero = " << std::boolalpha << none_lt_zero << '\n';
    // None less than zero = true

    // Use for_each to to call function on all members
    std::cout << "Squares: ";
    std::for_each(vec.cbegin(), vec.cend(), [](int x)
                  { std::cout << x * x << " "; });
    std::cout << '\n';
    // Squares: 1 1 4 9 25 64 169

    // Use transform to map values of vec into container halves
    std::vector<double> halves;
    std::transform(vec.cbegin(), vec.cend(), std::back_inserter(halves), [](int x)
                   { return x / 2.0; });
    std::cout << halves << '\n';
    // [0.5, 0.5, 1, 1.5, 2.5, 4, 6.5]

    // Capture variable by value
    double divisor = 3.0;
    std::vector<double> fractions;
    std::transform(vec.cbegin(), vec.cend(), std::back_inserter(fractions), [divisor](int x)
                   { return x / divisor; });
    std::cout << fractions << '\n';
    // [0.333333, 0.333333, 0.666667, 1, 1.66667, 2.66667, 4.33333]

    // Capture variable by reference
    int sum = 0;
    std::for_each(vec.cbegin(), vec.cend(), [&sum](int x)
                  { sum += x; });
    std::cout << "Sum of vec = " << sum << '\n';
    // Sum of vec = 33

    // Zip and multiply vec and factors
    std::vector<int> factors{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}};
    std::vector<int> products;
    std::transform(
        vec.cbegin(), vec.cend(), factors.cbegin(), std::back_inserter(products),
        [](int x, int y)
        { return x * y; });
    std::cout << products << '\n';
    // [0, 1, 4, 9, 20, 40, 78]

    // Filter elements greater than or equal threshold with copy_with
    int threshold = 5;
    std::vector<int> ge_threshold;
    std::copy_if(
        vec.cbegin(), vec.cend(), std::back_inserter(ge_threshold),
        [threshold](int x)
        { return x >= threshold; });
    std::cout << ge_threshold << '\n';
    // [5, 8, 13]

    // Use non-capturing(!) lambda as replacement for function pointer
    std::vector<double> fifth = map_int_to_double(vec, [](int x)
                                                  { return x / 5.0; });
    std::cout << fifth << '\n';
    // [0.2, 0.2, 0.4, 0.6, 1, 1.6, 2.6]

    // Use custom higher order function with capture
    double summand = .3;
    std::vector<double> added = map_with_function<int, double>(
        vec, [summand](int x)
        { return x + summand; });
    std::cout << added << '\n';
    // [1.3, 1.3, 2.3, 3.3, 5.3, 8.3, 13.3]

    // Sort some elements in descending order
    std::sort(vec.begin() + 2, vec.end() - 1, [](int a, int b)
              { return a > b; });
    std::cout << vec << '\n';
    // [1, 1, 8, 5, 3, 2, 13]

    std::vector<Person> persons{{Person{"Alice", 10}, Person{"Bob", 8}, Person{"Charles", 42}}};
    // Sort persons by name descending
    std::sort(persons.begin(), persons.end(), [](Person a, Person b)
              { return a.name > b.name; });
    std::cout << persons << '\n';
    // [Person(Charles, 42), Person(Bob, 8), Person(Alice, 10)]
    // Sort persons by age ascending
    std::sort(persons.begin(), persons.end(), [](Person a, Person b)
              { return a.age < b.age; });
    std::cout << persons << '\n';
    // [Person(Bob, 8), Person(Alice, 10), Person(Charles, 42)]

    // Use tricks to create a range of numbers
    std::vector<int> range;
    std::fill_n(std::back_inserter(range),20,0);
    int n = 1;
    std::transform(range.begin(),range.end(),range.begin(),[&n](int i){return n++;});
    std::cout << range << '\n';
    // [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]

    // Demonstrate Java-Style functional programming with the wrapper class
    auto result = 
    VectorWrapper<int>{range}
    .filter([](int x) {return x % 2 == 1;})
    .apply<int>([](int x) -> int {return x*x;})
    .apply<double>([](int x) -> double {return x / 2.0;})
    .sort([](double a, double b){return a>b;})
    .collect();
    std::cout << result << '\n';
    // [180.5, 144.5, 112.5, 84.5, 60.5, 40.5, 24.5, 12.5, 4.5, 0.5]

    return 0;
}