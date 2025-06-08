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
 * 设备策略 - mysql
 * @author Lm
 * @date 2022/11/6 15:02
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
@Table(name = "lm_device_strategy") //设置表名
@org.hibernate.annotations.Table(appliesTo = "lm_device_strategy", comment = "设备策略")
public class DeviceStrategy implements Serializable {

    // 策略id
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, columnDefinition = "BIGINT COMMENT '策略id'")
    private Long id;

    // 策略名称
    @Column(name = "name", nullable = true, columnDefinition = "varchar(100) COMMENT '策略名称'")
    private String name;

    // 策略描述（原字段名"describe"是SQL保留字，改为"description"避免冲突）
    @Column(name = "describe", nullable = true, columnDefinition = "varchar(100) COMMENT '策略描述'")
    private String describe;

    // 触发条件表达式字符串
    @Column(name = "triggerStr", nullable = true, columnDefinition = "text COMMENT '触发条件表达式字符串'")
    private String triggerStr;

    // 执行动作字符串
    @Column(name = "actionStr", nullable = true, columnDefinition = "text COMMENT '执行动作字符串'")
    private String actionStr;

    // 是否启用 0 不启用 1 启用
    @Column(name = "status", nullable = true, columnDefinition = "int(1) COMMENT '是否启用（0-不启用，1-启用）'")
    private Integer status;

    // 创建时间（JPA自动填充：插入时生成）
    @CreationTimestamp
    @Column(name = "createTime", columnDefinition = "datetime COMMENT '创建时间'")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date createTime;

    // 更新时间（JPA自动填充：插入/更新时生成）
    @UpdateTimestamp
    @Column(name = "updateTime", columnDefinition = "datetime COMMENT '更新时间'")
    @DateTimeFormat(pattern = "yyyy-MM-dd HH:mm:ss")
    private Date updateTime;
}