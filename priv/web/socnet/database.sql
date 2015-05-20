SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";
CREATE DATABASE `socnet` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE `socnet`;

CREATE TABLE `comment` (
  `wallid` bigint(20) NOT NULL,
  `fromid` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `msg` varchar(300) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `connect` (
  `id` int(11) NOT NULL,
  `friend` int(11) NOT NULL,
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `hash` varchar(32) NOT NULL,
  `email` varchar(255) NOT NULL,
  `sex` tinyint(4) NOT NULL,
  `born` date NOT NULL,
  `lastname` varchar(50) NOT NULL,
  `firstname` varchar(50) NOT NULL,
  `location` varchar(50) NOT NULL,
  `other` varchar(10000) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`),
  KEY `id_2` (`id`),
  KEY `id_3` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

CREATE TABLE `wall` (
  `id` bigint(20) NOT NULL,
  `fromid` int(11) NOT NULL,
  `date` date NOT NULL,
  `msg` varchar(1000) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `id` (`id`),
  KEY `id_2` (`id`),
  KEY `id_3` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
