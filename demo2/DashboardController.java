package com.grupp.sensor.demo2;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

@Controller
public class DashboardController {

    private final SensorRepo sensorRepo;

    public DashboardController(SensorRepo sensorRepo) {
        this.sensorRepo = sensorRepo;
    }

    @RequestMapping ("/dashboardd")
    public String showDashboard(Model model) {

        SensorData latest = sensorRepo.findTopByOrderByTimestampDesc();

        List<SensorData> history = sensorRepo.findTop10ByOrderByTimestampDesc();

        model.addAttribute("latest", latest);
        model.addAttribute("history", history);

        return "dashboard";
    }

    @RequestMapping("/add")
    @ResponseBody
    public SensorData addSensorData(@RequestParam double sensor_value) {
        return sensorRepo.save(new SensorData(sensor_value));
    }
}
