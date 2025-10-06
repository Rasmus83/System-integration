package com.grupp.sensor.demo2;

import jakarta.persistence.*;
import lombok.Data;
import org.hibernate.annotations.CreationTimestamp;

@Data
@Entity
@Table(name = "temperature_readings")
public class SensorData {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)

    protected long id;
    @Column(name = "temperature")
    protected double temperature;
    @CreationTimestamp
    @Column(name = "timestamp")
    protected String timestamp;

    public SensorData(double temperature) {
        this.temperature = temperature;
    }

    public SensorData() {}
}
