#include <wrapper.h>
#include <functional>
#include <map>

// Global map to store last execution times for different functions
static std::map<void *, unsigned long> lastMillisMap;

void asyncTimeout(const std::function<void()> &f, int delay)
{
    unsigned long currentMillis = millis();

    // Use the address of the function object as a unique identifier
    void *uniqueId = (void *)&f;

    // Initialize lastMillis for this function if it doesn't exist
    if (lastMillisMap.find(uniqueId) == lastMillisMap.end())
    {
        lastMillisMap[uniqueId] = 0;
    }

    unsigned long &lastMillis = lastMillisMap[uniqueId];

    // Serial.printf("Current Calculation Time for %p: %lu \n", uniqueId, currentMillis - lastMillis);

    if (currentMillis - lastMillis >= delay)
    {
        f();
        lastMillis = currentMillis;
    }
}