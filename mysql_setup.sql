-- MySQL 설정 SQL
-- 1818 포트로 연결하기 위한 데이터베이스 설정

CREATE DATABASE IF NOT EXISTS maze_game;
USE maze_game;

-- custom_game 테이블 생성
CREATE TABLE IF NOT EXISTS custom_game (
    id INT AUTO_INCREMENT PRIMARY KEY,
    width INT NOT NULL,
    height INT NOT NULL,
    start_point JSON NOT NULL COMMENT '시작점 좌표 {"x": 1, "y": 1}',
    end_point JSON NOT NULL COMMENT '끝점 좌표 {"x": 10, "y": 10}',
    wall JSON NOT NULL COMMENT '벽 위치 배열 [{"x": 2, "y": 3}, {"x": 4, "y": 5}]',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

-- 샘플 데이터 추가
INSERT INTO custom_game (width, height, start_point, end_point, wall) VALUES
(15, 15, '{"x": 1, "y": 1}', '{"x": 13, "y": 13}', '[{"x": 3, "y": 3}, {"x": 5, "y": 5}, {"x": 7, "y": 7}]'),
(20, 20, '{"x": 2, "y": 2}', '{"x": 18, "y": 18}', '[{"x": 4, "y": 4}, {"x": 8, "y": 8}, {"x": 12, "y": 12}]'),
(10, 10, '{"x": 1, "y": 1}', '{"x": 8, "y": 8}', '[{"x": 3, "y": 2}, {"x": 5, "y": 4}, {"x": 6, "y": 6}]');

-- 사용자 생성 및 권한 부여
CREATE USER IF NOT EXISTS 'maze_user'@'localhost' IDENTIFIED BY 'maze_password';
GRANT ALL PRIVILEGES ON maze_game.* TO 'maze_user'@'localhost';
FLUSH PRIVILEGES;