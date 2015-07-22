-- phpMyAdmin SQL Dump
-- version 2.10.2
-- http://www.phpmyadmin.net
-- 
-- 主机: localhost
-- 生成日期: 2011 年 01 月 21 日 09:29
-- 服务器版本: 5.0.45
-- PHP 版本: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- 数据库: `xpc_liuyanban`
-- 

-- --------------------------------------------------------

-- 
-- 表的结构 `lyb`
-- 

CREATE TABLE `lyb` (
  `id` int(11) NOT NULL auto_increment,
  `biaoti` varchar(200) NOT NULL,
  `neirong` text NOT NULL,
  `touxiang` varchar(200) NOT NULL,
  `nicheng` varchar(100) NOT NULL,
  `time` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

-- 
-- 导出表中的数据 `lyb`
-- 

INSERT INTO `lyb` VALUES (1, '²âÊÔ±êÌâ', '²âÊÔÄÚÈÝ', '03', '²âÊÔêÇ³Æ', 1295602131);
