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
 * 角色信息 mysql
 * @author Lm
 * @date 2022/11/22 8:14
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
@Table(name = "lm_roles") //设置表名
@org.hibernate.annotations.Table(appliesTo = "lm_roles", comment = "设备策略")
public class Roles implements java.io.Serializable {

    // 主键
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, columnDefinition = "BIGINT COMMENT '主键'")
    private Long id;

    // 角色代号
    @Column(name = "roleCode", nullable = true, columnDefinition = "varchar(100) COMMENT '角色代号'")
    private String roleCode;

    // 角色名称
    @Column(name = "roleName", nullable = true, columnDefinition = "varchar(100) COMMENT '角色名称'")
    private String roleName;

    // 	发布状态 0 禁用 1未禁用
    @Column(name = "status", nullable = true, columnDefinition = "int(1) COMMENT '是否启用（0-不启用，1-启用）'")
    private Integer	status;

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
