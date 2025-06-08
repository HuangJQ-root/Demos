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
 * 菜单管理
 * @author Lm
 * @since 2022-10-13
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
@Table(name = "lm_permission") //设置表名
@org.hibernate.annotations.Table(appliesTo = "lm_permission", comment = "设备策略")
public class Permission implements java.io.Serializable {

    // 主键
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, columnDefinition = "BIGINT COMMENT '主键'")
    private Long id;

    // 菜单名词
    @Column(name = "name", nullable = true, columnDefinition = "varchar(100) COMMENT '菜单名词'")
    private String name;

     // 菜单排序
     @Column(name = "sorted", nullable = true, columnDefinition = "int(11) COMMENT '菜单排序'")
    private Integer sorted;

     // 菜单链接
     @Column(name = "path", nullable = true, columnDefinition = "varchar(100) COMMENT '菜单链接'")
    private String path;

     // 菜单图标
     @Column(name = "icon", nullable = true, columnDefinition = "varchar(100) COMMENT '菜单图标'")
    private String icon;

     // 菜单发布
     @Column(name = "status", nullable = true, columnDefinition = "int(11) COMMENT '菜单发布'")
    private Integer status;

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

     // 菜单名称
     @Column(name = "pid", nullable = true, columnDefinition = "BIGINT COMMENT '父菜单ID'")
    private Long pid;

     // 路径名称
     @Column(name = "pathname", nullable = true, columnDefinition = "varchar(100) COMMENT '路径名称'")
    private String pathname;

     // 删除状态 0未删除 1删除
     @Column(name = "isdelete", nullable = true, columnDefinition = "int(1) COMMENT '删除状态 0未删除 1删除 '")
    private Integer isdelete;

     // 1菜单 2 权限
     @Column(name = "type", nullable = true, columnDefinition = "int(11) COMMENT ' 1菜单 2 权限'")
    private Integer type;

     // 代号
     @Column(name = "code", nullable = true, columnDefinition = "varchar(100) COMMENT '代号'")
    private String code;

}
