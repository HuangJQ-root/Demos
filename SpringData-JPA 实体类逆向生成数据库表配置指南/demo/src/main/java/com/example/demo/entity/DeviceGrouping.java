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
 * 设备分组实体 - mysql
 * @author Lm
 * @date 2022/10/31 15:34
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
@Table(name = "lm_device_grouping") //设置表名
@org.hibernate.annotations.Table(appliesTo = "lm_device_grouping", comment = "设备分组")
public class DeviceGrouping implements java.io.Serializable  {
    // 分组主键id
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, columnDefinition = "BIGINT COMMENT '分组id'")
    private Long id;

    // 分组名称
    @Column(name = "name", nullable = true, columnDefinition = "varchar(100) COMMENT '分组名称'")
    private String name;

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
