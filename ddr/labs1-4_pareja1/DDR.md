# Design & Decision Record (DDR) — Labs 1–4, Pair 1
**GreenField Technologies | IoT Systems Design**

**Team Members:**
1. Nicolas Castaño
2. Oscar Andres Tepud

> Labs 1–4 are done in pairs. From Lab 5 on, this pair and Pair 2 work as one team: see [the team DDR](../labs5-8_equipo/DDR.md).

---

## 1. System Overview

*   **System Type:** [ ] Component (Lab 1-2) | [ ] System (Lab 3-6) | [ ] Environment (Lab 7-8)
*   **Description:**

---

## 2. Lab Log & Stakeholder Summaries

### Lab 1: RF Characterization
*   **To Samuel (Architect):**
*   **To Edwin (Ops):**

### Lab 2: 6LoWPAN
*   **To Samuel:**

### Lab 3: Thread & CoAP
*   **To Daniela (Customer):**

### Lab 4: Real Sensors
*   **To Edwin:**

---

## 3. Architecture Decision Records (ADRs)

**ADR-___: [Title]**
*   **Context:**
*   **Decision:**
*   **Rationale:**
*   **Status:** [ ] Proposed | [ ] Accepted | [ ] Deprecated

---

## 4. ISO/IEC 30141 Mapping

### Domain Mapping

| Component | ISO Domain | Justification |
|-----------|------------|---------------|
|           |            |               |

### Component Capabilities

| Capability Category | Subcategory | Component/Feature | Active/Latent | Lab Introduced |
|---------------------|-------------|-------------------|---------------|----------------|
|                     |             |                   |               |                |

---

## 5. First Principles Reflections

**Lab 1:**
1.
2.

**Lab 2:**
1.

**Lab 3:**
1.

**Lab 4:**
1.

---

## 6. Performance Baselines

| Metric | Target | Measured | Status |
|--------|--------|----------|--------|
| Lab 1: Max Range | > 20m | ___ m | [ ] Pass |
| Lab 2: Healing Time | < 120s | ___ s | [ ] Pass |
| Lab 3: CoAP Latency | < 200ms| ___ ms | [ ] Pass |
| Lab 3: Poll Latency (5 s period) | < 5s | ___ s | [ ] Pass |
| Lab 4: Time to see a lost sensor | ≤ 60s | ___ s | [ ] Pass |
| Lab 4: Read failures, radio busy | < 5% | ___ % | [ ] Pass |

---

## 7. Ethics & Sustainability Checklist

*   [ ] **Lab 1:** Verified interference doesn't disrupt neighbors.
*   [ ] **Lab 4:** Safe default when sensor data is missing (Safety).

---

## 8. Viewpoint Analysis

| Viewpoint | Labs Addressed | Key Concerns Documented |
|-----------|----------------|-------------------------|
| Foundational |            |                         |
| Business |               |                         |
| Usage |                  |                         |
| Functional |             |                         |
| Trustworthiness |        |                         |
| Construction |           |                         |

---

## 9. Trustworthiness Audit (Lab 4+)

| Characteristic | Addressed? | How | Gaps |
|----------------|------------|-----|------|
| Availability |            |     |      |
| Confidentiality |         |     |      |
| Integrity |               |     |      |
| Reliability |             |     |      |
| Resilience |              |     |      |
| Safety |                  |     |      |
| Compliance |              |     |      |

---

## Evidence

Photos and screenshots go in [`img/`](img/), one folder per lab. Embed them next to the section they support:

```markdown
![Short description](img/lab1/file.jpg)
*Fig. 1.1 — What it shows and why it matters.*
```
