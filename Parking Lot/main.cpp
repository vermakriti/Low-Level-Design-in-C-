#include <bits/stdc++.h>
using namespace std;

class Vehicle;
class ParkingLot;
class Slot;

enum Color
{
    white,
    black,
    red,
    orange,
    green
};

enum Type{
    CAR,
    BIKE,
    TRUCK
};

vector<string> input_command(string &s){
    vector<string> v;
    string word;
    stringstream ss(s);
    while (ss >> word)
    {
        v.push_back(word);
    }
    return v;
}

Type getType(string vehicle_type){
    Type type;
    if (vehicle_type == "TRUCK"){
        type = TRUCK;
    }
    else if (vehicle_type == "BIKE"){
        type = BIKE;
    }
    else{
        type = CAR;
    }
    return type;
}

Color getColor(string color_type){

    Color color;
    if(color_type == "white")
        color = white;
    else if(color_type == "black")
        color = black;
    else if(color_type == "red")
        color = red;
    else if(color_type == "orange")
        color = orange;
    else
        color = green;
    return color;
}

class Slot{

    int slot_id;
    bool available;
    Type type;

public:
    Slot(int slot_id, Type type){
        this->slot_id = slot_id;
        this->available = true;
        this->type = type;
    }
    int getSlotId(){
        return slot_id;
    }
    int getAvailability(){
        return available;
    }
    Type getType(){
        return type;
    }
};

class Floor
{
    int floor_id;
    int slot_count;
    vector<Slot> slots;

public:
    
    Floor(int floor_id, int slot_count){
        this->floor_id = floor_id;
        this->slot_count = slot_count;

        for (int i = 0; i < slot_count; i++){
            if (i == 0){
                Type type = getType("TRUCK");
                Slot slot(i + 1, type);
                slots.push_back(slot);
            }
            else if (i < 3){
                Type type = getType("BIKE");
                Slot slot(i + 1, type);
                slots.push_back(slot);
            }
            else{
                Type type = getType("CAR");
                Slot slot(i + 1, type);
                slots.push_back(slot);
            }
        }
    }
    int getFloorId(){
        return floor_id;
    }
    int getSlotCount(){
        return slot_count;
    }
    vector<Slot> getSlots(){
        return slots;
    }
    int getAvailableSlot(Type type){
        for (int i = 0; i < slots.size();i++){
            if(slots[i].getAvailability() && slots[i].getType() == type)
                return slots[i].getSlotId();
        }
        return -1;
    }
    int getFreeSlotCount(Type type){
        int available = 0;
        for (int i = 0; i < slots.size();i++){
            if (slots[i].getType() == type && slots[i].getAvailability())
                available++;
        }
        return available;
    }
    vector<int> getFreeSlot(Type type){
        vector<int> available;
        for (int i = 0; i < slots.size();i++){
            if(slots[i].getType() == type && slots[i].getAvailability())
                available.push_back(slots[i].getSlotId());
        }
        return available;
    }
    vector<int> getOccupiedSlot(Type type){
        vector<int> available;
        for (int i = 0; i < slots.size();i++){
            if(slots[i].getType() == type && !slots[i].getAvailability())
                available.push_back(slots[i].getSlotId());
        }
        return available;
    }
};

class ParkingLot
{
    string parkingLot_id;
    int total_floor;
    vector<Floor> floors;
    unordered_map<int, unordered_map<int, Vehicle>> parked;

public:
   
    ParkingLot(string parkingLot_id, int total_floor, vector<Floor> floors)
    {
        this->parkingLot_id = parkingLot_id;
        this->total_floor = total_floor;
        this->floors = floors;
    }
    ParkingLot(string parkingLot_id, int total_floor, int slot_count)
    {
        this->parkingLot_id = parkingLot_id;
        this->total_floor = total_floor;

        for (int i = 0; i < total_floor; i++){
            Floor floor(i + 1, slot_count);
            floors.push_back(floor);
        }
    }
    vector<int> getFreeSlotCount(string &vehicle_type){

        vector<int> available;
        for (int floor_no = 0; floor_no < floors.size(); floor_no++){
            int count = floors[floor_no].getFreeSlotCount(getType(vehicle_type));
            available.push_back(count);
        }
        return available;
    }

    vector<vector<int>> getFreeSlots(string &vehicle_type){

        vector<vector<int>> available;
        for (int floor_no = 0; floor_no < floors.size(); floor_no++)
        {
            vector<int> c = floors[floor_no].getFreeSlot(getType(vehicle_type));
            available.push_back(c);
        }
        return available;
    }

    vector<vector<int>> getOccupiedSlots(string &vehicle_type){

        vector<vector<int>> available;
        for (int floor_no = 0; floor_no < floors.size(); floor_no++)
        {
            vector<int> c = floors[floor_no].getOccupiedSlot(getType(vehicle_type));
            available.push_back(c);
        }
        return available;
    }
    string addParking(string registration_number, string &vehicle_type, string &color){
        for (int i = 0; i < floors.size();i++){
            int slot = floors[i].getAvailableSlot(getType(vehicle_type));
            if(slot != -1){
                Vehicle vehicle(getColor(color), getType(vehicle_type), registration_number);
                parked[i + 1][slot] = vehicle;
                return "Parked";
            }
        }
        return "Parking Lot Full";
    }
};

class Vehicle
{
    Color color;
    Type type;
    string registration_number;

public:
   
    Vehicle(Color color, Type type, string registration_number)
    {
        this->color = color;
        this->type = type;
        this->registration_number = registration_number;
    }
    Color getColor()
    {
        return color;
    }
    Type getType()
    {
        return type;
    }
    string getRegistrationNumber()
    {
        return registration_number;
    }
};

int main(){

    string input;
    getline(cin, input);
    vector<string> c = input_command(input);
    cout << "Created parking lot with " + c[2] << " floors and " + c[3] + " slots per floor" << '\n';
    ParkingLot parkingLot(c[1], stoi(c[2]), stoi(c[3]));

    while (1)
    {
        getline(cin, input);
        if (input == "exit")
            break;
        vector<string> command = input_command(input);
        
        if (command[0] == "display")
        {
            if (command[1] == "free_count"){
                vector<int> output = parkingLot.getFreeSlotCount(command[2]);
                for (int i = 0; i < output.size(); i++) cout << "No. of free slots for " + command[2] + " on Floor " << i+1 << ": " << output[i] << "\n";
            }
            else if (command[1] == "free_slots"){
                vector<vector<int>> output = parkingLot.getFreeSlots(command[2]);
                for (int i = 0; i < output.size();i++){
                    cout << "Free slots for " + command[2] + " Floor " << i + 1 << ": ";
                    for (int j = 0; j < output[0].size(); j++)
                        cout << j + 1 << ",";
                    cout << "\n";
                }
            }
            else if (command[1] == "occupied_slots"){
                vector<vector<int>> output = parkingLot.getOccupiedSlots(command[2]);
                for (int i = 0; i < output.size();i++){
                    cout << "Occupied slots for " + command[2] + " Floor " << i + 1 << ": ";
                    for (int j = 0; j < output[0].size(); j++)
                        cout << j + 1 << ",";
                    cout << "\n";
                }
            }
        }
        else if(command[0] == "park_vehicle"){
            string status = parkingLot.addParking(command[2], command[1], command[3]);
            cout << status << "\n";
        }
        else{

        }
    }
}