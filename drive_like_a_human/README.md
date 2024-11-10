Setup Dev Environment

```bash
conda create -n drive_like_a_human python=3.8
conda activate drive_like_a_human

# for compatability, use conda to install packages at first, then use pip to install, to avoid compile issue
conda install flask=2.2.2 gymnasium=0.28.1 matplotlib=3.7.1 numpy=1.24.3 pyyaml=6.0 -c conda-forge 

# for langchain, openai, rich, use pip to install, since they might not be in conda install
pip install langchain==0.0.225 openai==0.27.7 rich==13.4.2

# open source minimalist environment for decision-making in autonomous driving simulation
pip install highway-env
conda install moviepy
pip install tiktoken

python -c "import yaml; print('PyYAML is installed')" # quick way to verify python library installation

```

```python
# OpenAI: We recommend choosing gpt-4o-mini where you would have previously used gpt-3.5-turbo as this model is more capable and cheaper.

elif OPENAI_CONFIG['OPENAI_API_TYPE'] == 'openai':
    os.environ["OPENAI_API_KEY"] = OPENAI_CONFIG['OPENAI_KEY']
    llm = ChatOpenAI(
        temperature=0,
        model_name='gpt-4o-mini', # or any other model with 8k+ context
        max_tokens=1024,
        request_timeout=60
    )

```

Troubleshooting
```python
# HELLM.py: import the repo
import highway_env # this must be included, otherwise gym cannot find  highway-v0 environment

# customTools.py: add unwrapped
availableActions = self.env.unwrapped.get_available_actions() 

# higyway_env -> abstract.py: only use self.render()
  def _automatic_rendering(self) -> None:
        """
        Automatically render the intermediate frames while an action is still ongoing.

        This allows to render the whole video and not only single steps corresponding to agent decision-making.
        If a RecordVideo wrapper has been set, use it to capture intermediate frames.
        """
        if self.viewer is not None and self.enable_auto_render:
            self.render()
            # if self._record_video_wrapper and self._record_video_wrapper.video_recorder:
            #     self._record_video_wrapper.video_recorder.capture_frame()
            # else:
            #     self.render()

# driverAgent.py output['thoughts'], output['answer'] = self.ch.memory[-1].split(
# ValueError: not enough values to unpack (expected 2, got 1)
def exportThoughts(self):
        output = {}
        if not self.ch.memory:
            raise ValueError("Memory is empty.")
        last_memory = self.ch.memory[-1]
        if ':' not in last_memory:
            raise ValueError("Expected ':' in the last memory entry.")
        output['thoughts'], output['answer'] = last_memory.split(':', 1)
        return output
# def exportThoughts(self):
#     print("Debug: self.ch.memory =", self.ch.memory)
#     output = {}
#     output['thoughts'], output['answer'] = self.ch.memory[-1].split(
#         'Final Answer:')
#     return output

```

Run the code
```bash
python HELLM.py


```