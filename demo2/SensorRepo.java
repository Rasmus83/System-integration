package com.grupp.sensor.demo2;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;


//Med MAVEN
public interface SensorRepo extends JpaRepository<SensorData, Long> {
    SensorData findTopByOrderByTimestampDesc();
    List<SensorData> findTop10ByOrderByTimestampDesc();
}

