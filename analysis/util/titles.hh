string get_level_title(string level) {
    //TODO: at some point mayber turn this into an unordered_map<string,string>
    string level_title;
    if      (level == "offline")    {level_title = "Offline";}
    else if (level == "online")     {level_title = "Hybrid Retuned Online";}
    else if (level == "online_official_tune") {level_title = "Online Tune RUN12-08-14";}
    else if (level == "ftk")        {level_title = "FTK-Based Online";}
    else                            {level_title = "Uncatagorized";}

    return level_title;
}

string get_event_title(string event) {
    string event_title = (event == "ttbar") ? "t#bar{t}" : "Z\'";
    
    return event_title;
}
