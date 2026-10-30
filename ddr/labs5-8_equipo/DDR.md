# Design & Decision Record (DDR) — Labs 5–8, Team L4F
**GreenField Technologies | IoT Systems Design**

**Team Members (Los4Fantasticos):**
1. Nicolas Castaño
2. Oscar Andres Tepud
3. Anderson Kaleth Angel
4. Camilo Obando

> Labs 1–4 were done in pairs; their records are in [Pair 1's DDR](../labs1-4_pareja1/DDR.md) and [Pair 2's DDR](../labs1-4_pareja2/DDR.md). Measurements this DDR compares against (for example the in-mesh RTT of Lab 3) come from there.

---

## 1. System Overview

*   **System Type:** [ ] Component (Lab 1-2) | [ ] System (Lab 3-6) | [ ] Environment (Lab 7-8)
*   **Description:**

---

## 2. Lab Log & Stakeholder Summaries

### Lab 5: Border Router
*   **To Daniela:**

### Lab 6: Security
*   **To Edward (Security):**

### Lab 7: Dashboard
*   **To Gustavo (Product):**

### Lab 8: Final Integration
*   **To All:**

---

## 3. Architecture Decision Records (ADRs)

**ADR-005: One OTBR for the pilot**
*   **Context:**
*   **Decision:**
*   **Rationale:**
*   **Status:** [ ] Proposed | [ ] Accepted | [ ] Deprecated

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

**Lab 5:**
1.
2.
3.
4.

**Lab 6:**
1.

**Lab 7:**
1.

**Lab 8:**
1.

---

## 6. Performance Baselines

| Metric | Target | Measured | Status |
|--------|--------|----------|--------|
| Lab 5: OTBR added latency | < 100ms | ___ ms | [ ] Pass |
| Lab 5: NAT64 RTT | < 200ms | ___ ms | [ ] Pass |
| Lab 6: DTLS Time | < 3s | ___ s | [ ] Pass |

---

## 7. Ethics & Sustainability Checklist

*   [ ] **Lab 5:** System works locally without cloud (Sustainability).
*   [ ] **Lab 6:** Encryption enabled (Privacy).
*   [ ] **Lab 8:** End-of-Life plan considered.

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

## 10. Construction Viewpoint - IoT System Pattern (Lab 8)

| Pattern Element | Category | Your System |
|-----------------|----------|-------------|
| IoT System |            |             |
| IoT Components |         |             |
| Digital Network |        |             |
| IoT Devices |            |             |
| Primary Capability (observation) | |   |
| Primary Capability (control) | |       |
| Secondary Capability (processing) | |  |
| Secondary Capability (transferring) | | |
| Secondary Capability (storage) | |     |
| Interface (network) |    |             |
| Interface (human UI) |   |             |
| Interface (application) | |            |
| Supplemental (security) | |            |
| Supplemental (orchestration) | |       |
| Supplemental (management) | |          |

---

## Evidence

Photos and screenshots go in [`img/`](img/), one folder per lab. Embed them next to the section they support:

```markdown
![Short description](img/lab5/file.jpg)
*Fig. 5.1 — What it shows and why it matters.*
```
