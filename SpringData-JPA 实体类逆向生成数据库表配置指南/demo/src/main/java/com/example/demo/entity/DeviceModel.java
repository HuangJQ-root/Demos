package com.example.demo.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.Date;

import javax.persistence.*;
import org.hibernate.annotations.CreationTimestamp;
import org.hibernate.annotations.UpdateTimestamp;
import org.springframework.format.annotation.DateTimeFormat;

/**
 * 设备物模型数据 - mysql
 * @author Lm
 * @date 2022/10/12 9:40
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
@Table(name = "lm_device_model") //设置表名
@org.hibernate.annotations.Table(appliesTo = "lm_device_model", comment = "设备物模型")
public class DeviceModel implements Serializable {

    // 雪花
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, columnDefinition = "BIGINT COMMENT '设备主键'")
    private Long id;

    // 对应的设备sn
    @Column(name = "sn", nullable = true, columnDefinition = "varchar(100) COMMENT '设备sn'")
    private String sn;

    // 对应设备id
    @Column(name = "deviceId", nullable = false, columnDefinition = "BIGINT COMMENT '设备id'")
    private Long deviceId;

    // 图标
    @Column(name = "icon", nullable = true, columnDefinition = "varchar(100) COMMENT '图标'")
    private String icon;

    // 数据名称
    @Column(name = "name", nullable = true, columnDefinition = "varchar(100) COMMENT '数据名称'")
    private String name;

    // 数据单位 值后面的参数 例->50℃
    @Column(name = "unit", nullable = true, columnDefinition = "varchar(100) COMMENT '数据单位'")
    private String unit;

    // 标识符 用于设备数据上报后查询对应的属性名称
    @Column(name = "identifier", nullable = true, columnDefinition = "varchar(100) COMMENT '属性名称'")
    private String identifier;

    // 数据 类型 int string bool、、
    @Column(name = "dataType", nullable = true, columnDefinition = "varchar(100) COMMENT '数据类型'")
    private String dataType;

    // 数据 类型描述 bool可以用
    @Column(name = "dataSpecs", nullable = true, columnDefinition = "varchar(100) COMMENT ' 数据类型描述'")
    private String dataSpecs;

    // 模型 类型   0是传感器 1是开关量 其他待定
    @Column(name = "modelType", nullable = true, columnDefinition = "int(1) COMMENT ' 模型类型  0是传感器 1是开关量'")
    private Integer modelType;

    // 创建时间
    @CreationTimestamp
    @Column(name = "createTime", columnDefinition = "datetime COMMENT '创建时间'")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date createTime;

    // 更新时间
    @UpdateTimestamp
    @Column(name = "updateTime", columnDefinition = "datetime COMMENT '更新时间'")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date updateTime;
}
