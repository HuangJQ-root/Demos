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
 * 用户信息 - mysql
 * @author Lm
 * @date 2022/11/21 15:15
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
@Table(name = "lm_user") //设置表名
@org.hibernate.annotations.Table(appliesTo = "lm_user", comment = "设备策略")
public class User implements java.io.Serializable {

    // 主键
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, columnDefinition = "BIGINT COMMENT '主键'")
    private Long id;

    // 名称、姓名
    @Column(name = "username", nullable = true, columnDefinition = "varchar(100) COMMENT '姓名'")
    private String username;

    // 账号
    @Column(name = "account", nullable = true, columnDefinition = "varchar(100) COMMENT '账号'")
    private String account;

    // 头像url
    @Column(name = "avatar", nullable = true, columnDefinition = "varchar(100) COMMENT '头像url'")
    private String avatar;

    // 密码
    @Column(name = "password", nullable = true, columnDefinition = "varchar(100) COMMENT '密码'")
    private String password;

    // 发布状态 0 禁用 1未禁用
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
