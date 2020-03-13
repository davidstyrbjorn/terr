#include"../include/core/clock.h"

terr::Clock::Clock() {
	m_startedAt = 0;
	m_pausedAt = 0;
	m_paused = false;
	m_started = false;
}

bool terr::Clock::isStarted() {
	return m_started;
}

bool terr::Clock::isStopped() {
	return !m_started;
}

bool terr::Clock::isPaused() {
	return m_paused;
}

bool terr::Clock::isActive() {
	return !m_paused & m_started;
}

void terr::Clock::pause() {
	if (m_paused || !m_started)
		return;

	m_paused = true;
	m_pausedAt = clock();
}

void terr::Clock::resume() {
	if (!m_paused)
		return;

	m_paused = false;
	m_startedAt = clock() - m_pausedAt;
}

void terr::Clock::stop() {
	m_started = false;
}

void terr::Clock::start() {
	if (m_started)
		return;

	m_started = true;
	m_paused = false;
	m_startedAt = clock();
}

void terr::Clock::reset() {
	m_paused = false;
	m_startedAt = clock();
}

clock_t terr::Clock::getTicks()
{
	if (!m_started)
		return 0;
	if (m_paused)
		return m_pausedAt - m_startedAt;
	return clock() - m_startedAt;
}